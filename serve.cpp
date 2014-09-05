#include "socklib.h"
#include "strplay.h"
using namespace std;
char path[]="/data/data";


void read_data(DATA &data)
{
<<<<<<< HEAD
	int len;
	NODE temp;
    while(fgets(temp.str,BUFFER,data.fp)!=NULL)
	{
	      len=temp.play();
//		  serve.send(temp.ans,len);
		  cout<<temp.ans;
	}
=======
<<<<<<< HEAD
	
=======
	     
>>>>>>> d8d585ead6c010090ade7986e5632ef0349440ea
>>>>>>> 4c0fe5afbd58a31d8512718c1bb2be06d7b06342
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
