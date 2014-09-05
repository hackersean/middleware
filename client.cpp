#include "socklib.h"
#define MAX 4096
#define THREAD 2
char buff[MAX];
char info[]="sta\0safasdft\r";

FILE *file;
pthread_t pid[THREAD];

//function

inline void oops(char str[]){
	    perror(str);
	    exit(1);
}


void *writefile(void* arg)
{
	
	 c_client *ceve=(c_client *)arg;
	 int x;
	 /*
	 while(true)
	 {
		 ceve->send(info);
		 x=ceve->recv(buff,MAX);
		 if(x==0) break;
		 fwrite(buff,x,1,file);
	 }
	 fclose(file);
     */
	 for(int i=0;i<=5;i++)
	{
		  ceve->send("go",sizeof "go");
	}

} 
void *test(void* arg)
{
	
	 c_client *ceve=(c_client *)arg;
	 int x;
	 /*
	 while(true)
	 {
		 ceve->send(info);
		 x=ceve->recv(buff,MAX);
		 if(x==0) break;
		 fwrite(buff,x,1,file);
	 }
	 fclose(file);
     */
	 for(int i=0;i<=5;i++)
	{
		  ceve->send("hi",sizeof "hi");
	}

} 

int main(int ac,char *av[])
{
        if(ac!=4)
        {
			    perror("argument error");
		} 
		
		int port=atoi(av[2]); 
		cout<<av[1]<<" "<<port<<endl;
		
		c_client ceve(av[1],port); 
        if((file=fopen(av[3],"w"))==NULL)
			 oops("fwrite fail");
   /*
		for(int i=0;i<THREAD;i++)
	   {
	      
         
	   }
	   */
       pthread_create(&pid[1],NULL,writefile,&ceve);
	   pthread_create(&pid[2],NULL,test,&ceve);
		
		pthread_join(pid[0],NULL);
       pthread_join(pid[1],NULL);
		for(int i=0;i<THREAD;i++)
	    {
     //        pthread_join(pid[i],NULL);
		}
		
	   
			   
		
         return 0;
}
