#include "socklib.h"

#define MAX 4096
#define THREAD 7

char buff[MAX];
FILE *file;
pthread_t pid[THREAD];
static int count=THREAD;                     //request count
sem_t *sem;

inline void oops(char str[]){
	    perror(str);
	    exit(1);
}

//=======receve data==========
void *receive(void* arg)
{
	 int len=0;
	 c_client *ceve=(c_client *)arg;
	 while(true)
	 {
		 len=ceve->recv(buff,MAX);
		 if(len==0) break;
		 fwrite(buff,len,1,file);
	 }
	 fclose(file);
     
}
//===================


//=========send request=========
void *request(void* arg)
{
	
	 c_client *ceve=(c_client *)arg;
	 int x;
	 while(true)
	{
		  ceve->send("g",1);
	}
}
//====================

//--------------------------------------------
int main(int ac,char *av[])
{
        if(ac!=4)
        {
			    perror("argument error");
		} 
		
		int port=atoi(av[2]); 
		cout<<av[1]<<" "<<port<<endl;
		sem_init(sem, 0,0);  
		
        
//=========receve data==========
        c_client cev(av[1],port); 
        pthread_t cev_pid;
        
        if((file=fopen(av[3],"w"))==NULL)
			 oops("fwrite fail"); 
	    
	    pthread_create(&cev_pid,NULL,receive,&cev);
	    
//===========================

// =======request thread pool=======
        c_client req(av[1],port); 
		for(int i=0;i<THREAD;i++)
	   {
               pthread_create(&pid[i],NULL,request,&req);
               sem_wait(sem);
	   }
		cout<<"ok"<<endl;

		
// ======================
//=============waite thread=====
/* 
		for(int i=0;i<THREAD;i++)
	    {
             pthread_join(pid[i],NULL);
		}
*/
		pthread_join(cev_pid,NULL);
		
		cout<<"over"<<endl;
         return 0;
}
