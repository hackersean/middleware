#include "socklib.h"
#include "strplay.h"
using namespace std;
char path[]="/data/data";



void data_transfer(int fd)
{
	     
}


int main(int ac,char *av[])
{
	if(ac!=2)
	{
		//	oops("argument error");
	} 
	
//	c_serve serve(atoi(av[1]));

//	 data_transfer(serve.accept());
	 
	DATA data(path); 

	NODE node(&data); //printf("hello");
//      cout<<data.buf<<endl;
    int len;   
	while((len=node.make())>0)
	{
		for(int i=0;i<len;++i)
			printf("%c",node.ans[i]);
	}
	cout<<"end"<<endl;
	
	
	
	 return 0;
}
