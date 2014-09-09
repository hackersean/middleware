#include "socklib.h"
#include "strplay.h"
using namespace std;
#define REQ_BUFF 300

char path[]="/data/data";
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
			  if(count==0) continue;
			  len=temp.play();
			  send(fd,temp.ans,len,0);
			  __sync_sub_and_fetch(&count,1); 
		}
}
//========================


//======receve request=========
void *request(void *arg)
{
	int fd=*(int*)arg;
    int x;
    while((x=recv(fd,req_buff,REQ_BUFF,0))==true)
	{
		   __sync_add_and_fetch(&count,x); 
	} 
}
//=========================

int main(int ac,char *av[])
{
	if(ac!=2)
	{
		oops("argument error");
	} 
//	cout<<"start"<<endl;
	c_serve serve(atoi(av[1]));
	cout<<"start"<<endl;
	
//======data transform=======
    DATA data(path);                   //read data
    
    int res=serve.accept();
    pthread_t res_pid;
    void *arg[]={&res,&data};
    pthread_create(&res_pid,NULL,response,arg);
//==============================================	
//======receve request thread====
    int req=serve.accept();
    pthread_t req_pid;
	pthread_create(&req_pid,NULL,request,&req);
//=======================
	pthread_join(res_pid,NULL);
cout<<endl<<"over"<<endl;
	 return 0;
}
