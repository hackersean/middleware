#include "socklib.h"
#include "strplay.h"
using namespace std;
char path[]="/data/data";



void data_transfer(int fd)
{
<<<<<<< HEAD
	
=======
	     
>>>>>>> d8d585ead6c010090ade7986e5632ef0349440ea
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

	NODE node(&data);
//      cout<<data.buf<<endl;
    int len;
	while((len=node.make())>0)
	{
	     printf("%s",node.ans);
//		 getchar();
	}
	
//	cout<<"over"<<endl;
	
	 return 0;
}
