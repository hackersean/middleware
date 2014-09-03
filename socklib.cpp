#include "socklib.h"
void inline oops(string as)
{
	    perror(as.c_str());
	    exit(1);
}

c_serve::c_serve(int port)     //绑定一个本地套接字
{


       if((fd=socket(AF_INET,SOCK_STREAM,0))<0)    //apply socket
       {
		        oops("c_serve socket apply fialled");
		}
       
       //write struct info
       bzero(&addr,sizeof addr);
       addr.sin_family=AF_INET;
       addr.sin_port=htons(port);
       addr.sin_addr.s_addr=htonl(INADDR_ANY);
    
       //bin socket
       
       if(bind(fd,(sockaddr*) &addr,sizeof addr)<0)
       {
		       oops("bind error");   
		}
		//start listen
		if(listen(fd,255)<0)
		{
		       oops("listen error");
		}
}
int c_serve::accept()
{
	     int c_client;
	     if((c_client =::accept(fd,NULL,NULL))<0)
	     {
		        oops("accept error");	
		 }  
		 return c_client;
}



c_client::c_client(string host,int port)
{
	     if((fd=socket(AF_INET,SOCK_STREAM,0))<0)    //apply socket
        {
		        oops("c_client socket apply fialled");
		}
		
         //struct 
         addr.sin_family = AF_INET;  
         addr.sin_port = htons(port);  
         addr.sin_addr.s_addr = inet_addr(host.c_str());  
         
         connect(fd, (sockaddr *)& addr, sizeof(addr));
}

int c_client::send(char buffer[],int len=M_BUFFER,int flag=0)
{
         return ::send(fd,buffer,len,flag);
}

int c_client::recv(char buffer[],int len=M_BUFFER,int flag=0)
{
         return ::recv(fd,buffer,len,flag);
}


