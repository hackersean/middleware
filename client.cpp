#include "socklib.h"

#define MAX 4096
#define THREAD 46

char buff[MAX];
FILE *file;
pthread_t pid[THREAD];
static int count=THREAD;                     //request count

pthread_mutex_t flag[THREAD];
queue <int> q;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;



inline void oops(char str[]){
	    perror(str);
	    exit(1);
}

//=======receve data==========
void *receive(void* arg)
{
	 int len=0;
	 int temp;

	 c_client *ceve=(c_client *)arg;
	 while(true)
	 {
		 len=ceve->recv(buff,MAX);
//		 cout<<buff<<endl;
		 if(len==0) break;
		 for(int i=0;i<len;i++)
		 {
			 if(buff[i]=='\n')
			 {
                pthread_mutex_lock(&mutex);
                if(q.empty()!=true)
				{
//					cout<<"unlock "<<q.front()<<endl;
					pthread_mutex_unlock(&flag[q.front()]);
					q.pop();
			    }
				
				pthread_mutex_unlock(&mutex);
			 }
		 }
		 fwrite(buff,len,1,file);    
	 }
	 fclose(file);
     
}
//===============================


//=========send request=========
void *request(void* arg)
{
	c_client *ceve=(c_client *)arg;
	int id=__sync_sub_and_fetch(&count,1);
    
	while(true)
	{
//		  cout<<"lock "<<id<<endl;
		  pthread_mutex_lock(&flag[id]);
		  ceve->send("g",1);	
		  pthread_mutex_lock(&mutex);
          q.push(id);
		  pthread_mutex_unlock(&mutex);
	}
}
//====================================

//--------------------------------------------
int main(int ac,char *av[])
{
//=============time==================
       timeval starttime;
	   timeval endtime; 
       gettimeofday(&starttime,0);
//====================================
  
  



        if(ac!=4)
        {
			    perror("argument error");
		} 
		
		int port=atoi(av[2]); 
		
		
		for(int i=0;i<THREAD;i++)
	    {
		    pthread_mutex_init(&flag[i],NULL);
		}
		
//		cout<<av[1]<<" "<<port<<endl;	
        
//=========receve data==========
        c_client cev(av[1],port); 
//        cev.send("receve data\n\0",sizeof("receve data\n\0"));

        pthread_t cev_pid;
        if((file=fopen(av[3],"w"))==NULL)
			 oops("fwrite fail"); 
	    
	    pthread_create(&cev_pid,NULL,receive,&cev);
	    
//===========================

// =======request thread pool=======
       c_client req(av[1],port); 

//       req.send("receve request\n\0",sizeof("receve request\n\0"));

		for(int i=0;i<THREAD;i++)
	   {
		   pthread_create(&pid[i],NULL,request,&req);
	   }
	
//	   cout<<"ok"<<endl;

		
// =============================
//=============waite thread=====
/* 
		for(int i=0;i<THREAD;i++)
	    {
             pthread_join(pid[i],NULL);
		}
*/
		pthread_join(cev_pid,NULL);
		
		
//=======================time==================		
        gettimeofday(&endtime,0);
        unsigned long long timeuse  = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
        timeuse /=1000;        //除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时
        printf("count=%llu",timeuse);
		fflush(stdout);

 //============================================
         return 0;
}
