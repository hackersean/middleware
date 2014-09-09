#include "socklib.h"
#include "strplay.h"
using namespace std;
#define REQ_BUFF 1

char *path;
char req_buff[REQ_BUFF];
static int count=0;                           //请求数

//======response data=========
void *response(void *tp)
{
	   int fd=*(int *)((void **)tp)[0];
	   DATA *data=(DATA *)((void **)tp)[1];
       int len=0;
	   NODE temp;

		while(fgets(temp.str,BUFFER,data->fp)!=NULL)
		{
			  //cout<<"response "<<count<<endl;
			  while(count==0)
			 {
			  }
			  len=temp.play();
			  send(fd,temp.ans,len,0);
			  __sync_sub_and_fetch(&count,1); 
//			  cout<<"respons "<<count<<endl;
		}
//		cout<<"end"<<endl;
}
//========================


//======receve request=========
void *request(void *arg)
{
//	cout<<"arg "<<arg<<endl;
	int fd=*(int*)arg;
//	cout<<"fd "<<fd<<endl;
    int x;
    while((x=recv(fd,req_buff,REQ_BUFF,0))==true)
	{      
		   __sync_add_and_fetch(&count,x); 
//		   cout<<"request "<<x<<" "<<count<<endl;
	} 
}
//=========================

int main(int ac,char *av[])
{
	if(ac!=3)
	{
		oops("argument error");
	} 
//	cout<<"start"<<endl;
	c_serve serve(atoi(av[2]));
	cout<<"start"<<endl;
	
//======data transform=======
    DATA data(av[1]);                   //read data
    
    int res=serve.accept();
    
/*	recv(res,req_buff,REQ_BUFF,0);
   	cout<<req_buff<<endl;
*/    
	pthread_t res_pid;
	void *arg[]={&res,&data};
    pthread_create(&res_pid,NULL,response,arg);
//==============================================	
//======receve request thread====
    int req=serve.accept();
    pthread_t req_pid;
    
//	recv(req,req_buff,REQ_BUFF,0);
//    cout<<req_buff<<endl;
//    cout<<"req fd "<<req<<" "<<&req<<endl;
	pthread_create(&req_pid,NULL,request,&req);
//=======================
	pthread_join(res_pid,NULL);
     cout<<"over"<<endl;
	 return 0;
}
