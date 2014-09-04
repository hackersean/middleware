#include "socklib.h"

using namespace std;




int main(int ac,char *av[])
{
        if(ac!=3)
        {
			    perror("argument error");
		} 
		char info[]="start\r";
		int port=atoi(av[2]); 
		c_client ceve(av[1],port); 
	   // ceve.send(info,sizeof info);
	    char buff[M_BUFFER];
	    ceve.socket_config(0);
	    
		int flag=fork();
		if(flag==0)
		{
    //               c_client client(av[1],port);
		}
		else if(flag>0)                                       //father
		{
		         
		        cout<<"fork"<<endl;
			    int x;
		         while(true)
		         {
		//		     sleep(1);
		                      x=ceve.recv(buff);
					      for(int i=0;i<x;i++)   cout<<buff[i];
				      if(x==0) break;
				 }
		}
		else
		{
		         oops("fork error");
		}
		
		
		
         return 0;
}
