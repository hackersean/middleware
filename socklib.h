#ifndef __SOCKLIB__
#define __SOCKLIB__

#include "config.h"
using namespace std;
#define M_BUFFER 300


class c_serve
{
        int fd; 
        sockaddr_in addr;
      public:
        c_serve(int port);
        int accept();
};

class c_client
{
	     int fd;
	     sockaddr_in addr;
	     public:
         c_client(string host,int port);
         int send(char buffer[],int len=M_BUFFER,int flag=0);
         int recv(char buffer[],int len=M_BUFFER,int flag=0);
         void socket_config(int f=0);
};



#endif
