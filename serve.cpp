#include "socklib.h"
#include "strplay.h"
using namespace std;
char path[]="/data/data";


void read_data(DATA &data)
{
	int len;
	NODE temp;
    while(fgets(temp.str,BUFFER,data.fp)!=NULL)
	{
	      len=temp.play();
//		  serve.send(temp.ans,len);
		  cout<<temp.ans;
	}
	
	     
}

int main(int ac,char *av[])
{
	if(ac!=2)
	{
		//	oops("argument error");
	} 
	
//	c_serve serve(atoi(av[1]));

//	serve.accept();
	 
	DATA data(path); 
	read_data(data);
	

	
//	cout<<"over"<<endl;
	
	 return 0;
}
