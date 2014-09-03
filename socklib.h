#ifndef __SOCKLIB__
#define __SOCKLIB__

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
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

void inline oops(string as)
{
	    perror(as.c_str());
	    exit(1);
}

#endif
