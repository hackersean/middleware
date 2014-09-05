#include "socklib.h"

using namespace std;


inline void oops(char str[]){
	    perror(str);
	    exit(1);
}



int main(int ac,char *av[])
{
        if(ac!=4)
        {
			    perror("argument error");
		} 
		char info[]="start\r";
		int port=atoi(av[2]); 
		cout<<av[1]<<" "<<port<<endl;
//		getchar();
		c_client ceve(av[1],port); 
	   // ceve.send(info,sizeof info);
	    char buff[M_BUFFER];
//	    ceve.socket_config(0);
	    
		int flag=fork();
		if(flag==0)
		{
    //               c_client client(av[1],port);
		}
		else if(flag>0)                                       //father
		{
		        FILE *file;
				if((file=fopen(av[3],"w"))==NULL)
					oops("fwrite fail");
//		        cout<<"fork"<<endl;
			    int x;
		         while(true)
		         {
					 ceve.send(info);
		//		     sleep(1);
		             x=ceve.recv(buff);
//					 cout<<x<<endl;
				     if(x==0) break;
					 fwrite(buff,x,1,file);
				 }
				 fclose(file);
		}
		else
		{
		         oops("fork error");
		}
		
		
		
         return 0;
}
