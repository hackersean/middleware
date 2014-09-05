#include "socklib.h"
#include "strplay.h"
using namespace std;
char path[]="/data/data";


void read_data(DATA &data,int fd)
{
<<<<<<< HEAD
=======
	int len;
	NODE temp;
    while(fgets(temp.str,BUFFER,data.fp)!=NULL)
	{
	      len=temp.play();
          send(fd,temp.ans,len,0);
		  
	}
>>>>>>> c1ef8771762ae1cf5750184b2cbc11e4d87c9220
}

int main(int ac,char *av[])
{
	if(ac!=2)
	{
		oops("argument error");
	} 
	
	c_serve serve(atoi(av[1]));

	int fd=serve.accept();
	 
	DATA data(path); 
	read_data(data,fd);
	

	
//	cout<<"over"<<endl;
	
	 return 0;
}
