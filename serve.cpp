#include "socklib.h"
#include "strplay,h"
using namespace std;

char * read_data(char path[])
{
    int fd = open(path,O_RDONLY);
    int len = lseek(fd,0,SEEK_END);
    char *buff = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);    
    return  buff;
}

void data_transfer(int fd)
{
	       
}


int main(int ac,char *av[])
{
        if(ac!=2)
        {
			    perror("argument error");
		} 
		 
	//	c_serve serve(atoi(av[1]));

	//	 data_transfer(serve.accept());
		 
		 char *buff=read_data("/data/data");
        
		cout<<"end"<<endl;
		
		
		
         return 0;
}
