#include "socklib.h"
#include "strplay.h"
using namespace std;
#define REQ_BUFF 256



char *path;
char req_buff[REQ_BUFF];
static volatile  int count=0;      //请求数
pthread_t pid[THREAD+10];

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
	{   
	    __sync_add_and_fetch(&pw,1);                    //读入
	}
    __sync_add_and_fetch(&frd,1); 
	 
}

int iogets(char* &str)
{  
    while(pt==pw)
	{
	    if(frd==1) exit(0);
	}
    str=iotemp[pt].str;
    __sync_add_and_fetch(&pt,1); 
	
    return 1;
}

//============================
//======response data=========
int tj=0;
void *response(void *tp)
{
	   int fd=*(int *)tp;
       int len=0;
	    NODE temp;
		while(iogets(temp.str)>0)
		{     
			  while(count==0)
			 {     
				  tj=0;
				  ++tj;
			  }  
              //cout<<tj<<endl;
			  len=temp.play();
			  
			  send(fd,temp.ans,len,0);
			  __sync_sub_and_fetch(&count,1); 
			  
//			  cout<<"count "<<count<<endl;
		} 
		cout<<tj<<endl;
//		cout<<"end"<<endl;
}
//========================


//======receve request=========
void *request(void *arg)
{
	int fd=*(int*)arg;
    int x;
    while((x=recv(fd,req_buff,REQ_BUFF,0))>0)
	{      
		   __sync_add_and_fetch(&count,x); 
//		   cout<<"x "<<x<<" "<<count<<endl;
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
	c_serve serve(atoi(av[2]));                         //socket创建
	
//========io asny============

   pthread_t io_pid;
   pthread_create(&io_pid,NULL,ioasny,av[1]);  



//===========================
//======data transform=======
    int res=serve.accept();                             //建立数据连接
    cout<<"start"<<endl;
	pthread_t res_pid;
    pthread_create(&res_pid,NULL,response,&res);


//==============================================	
//======receve request thread====
    int req,pi=0;
    while(pi<THREAD)
	{ 
	    req=serve.accept();
	    pthread_create(&pid[pi],NULL,request,&req);        //建立请求连接
	    ++pi;
	}

//=======================
	pthread_join(res_pid,NULL);
	cout<<tj<<endl;
     cout<<"over"<<endl;
	 return 0;
}
