#ifndef __SDATA__
#define __SDATA__

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/mman.h>   //mmap头文件

#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#define LL long long
#define BUFFER 300



class DATA
{
	public:
	 int fd;
	 LL xln;
	 char *ptr,*end;
	 char *buf;
   
     DATA(char *path=NULL);
};

class NODE            //处理节点
{   
	public:
     LL num;
	 DATA *data;
	 char ans[BUFFER];
     void play(char *str,LL len);
     LL make();
    
      
     NODE(DATA *);
};






#endif
