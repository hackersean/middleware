#include "socklib.h"
#include "strplay.h"
using namespace std;
#define REQ_BUFF 46

char *path;
char req_buff[REQ_BUFF];
static volatile  int count=0;      //请求数

struct IOS
{
	char str[BUFFER];
};
IOS* iotemp;
static LL pt=0,pw=0;
bool frd=0;

//============io==============

void *ioasny(void *arg)
{
	iotemp=new IOS[10474544];
	pt=0,pw=0;
    DATA data((char *)arg);        //read data
    while(fgets(iotemp[pw].str,BUFFER,data.fp)!=NULL)
	{  //cout<<"ioa "<<pw<<" "<<pt<<endl<<iotemp[pw].str<<endl;
	    __sync_add_and_fetch(&pw,1);                    //读入
	}

	//cout<<pw<<endl;
}

int iogets(char* &str)
{   //cout<<pt<<" "<<pw<<endl;
    while(pw==pt)
	{
	    if(frd==1) exit(0);
	}
    str=iotemp[pt].str;
    __sync_add_and_fetch(&pt,1); 
	__sync_add_and_fetch(&frd,1); 
    return 1;
}

//============================
//======response data=========
void *response(void *tp)
{
	   int fd=*(int *)tp;
       int len=0;
	   NODE temp;
//cout<<"response ok"<<endl;
		while(iogets(temp.str)>0)
		{
//			  cout<<"response 1:"<<count<<endl;
			  while(count==0)
			 {    
//				  sleep(1);
//				  cout<<"response count:"<<count<<endl;
			  }
			  len=temp.play();
			  send(fd,temp.ans,len,0);
			  __sync_sub_and_fetch(&count,1); 
//			  cout<<"respons 2:"<<count<<endl;
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
    while((x=recv(fd,req_buff,REQ_BUFF,0))>0)
	{      
		   __sync_add_and_fetch(&count,x); 
///		   cout<<"request "<<x<<" "<<count<<endl;
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
	
//========io asny============

   pthread_t io_pid;
   pthread_create(&io_pid,NULL,ioasny,av[1]);  

 //   cout<<"woca"<<endl;


//===========================
//======data transform=======
    
    
    int res=serve.accept();
    cout<<"start"<<endl;
/*	recv(res,req_buff,REQ_BUFF,0);
   	cout<<req_buff<<endl;
*/    
	pthread_t res_pid;
    pthread_create(&res_pid,NULL,response,&res);
//==============================================	
//======receve request thread====
    int req=serve.accept();
    pthread_t req_pid;
    
//	recv(req,req_buff,REQ_BUFF,0);
//    cout<<req_buff<<endl;
 //   cout<<"req fd "<<req<<" "<<&req<<endl;
	pthread_create(&req_pid,NULL,request,&req);
//=======================
	pthread_join(res_pid,NULL);
     cout<<"over"<<endl;
	 return 0;
}
