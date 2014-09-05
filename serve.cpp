#include "socklib.h"
#include "strplay.h"
using namespace std;
char path[]="/data/data";
char buff[BUFFER];

void read_data(DATA &data,int fd)
{
	int len;
	NODE temp;
/*	
    while(fgets(temp.str,BUFFER,data.fp)!=NULL)
	{
		  recv(fd,buff,BUFFER,0);
	      len=temp.play();
          send(fd,temp.ans,len,0);
		  
	}
*/
    while(true)
	{
           recv(fd,buff,BUFFER,0);
		   cout<<buff<<endl;
	}
}

int main(int ac,char *av[])
{
	if(ac!=2)
	{
		oops("argument error");
	} 
//	cout<<"start"<<endl;
	c_serve serve(atoi(av[1]));

	int fd=serve.accept();
	cout<<"start"<<endl;
	DATA data(path); 
	read_data(data,fd);
	
	cout<<"over"<<endl;
	
	 return 0;
}
