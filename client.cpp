#include "socklib.h"

#define MAX 4096
#define THREAD 72


int pt=0,pw=0,pr=0;
bool frd=0;
struct IOS
{
    char buff[MAX];
	int len;
};

IOS *iotemp;
FILE *file;
pthread_t io_pid;
static int count=THREAD;                     //request count

timeval starttime;
timeval endtime; 

pthread_t pid[THREAD];
bool bj[THREAD];
pthread_mutex_t flag[THREAD];
 
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;



inline void oops(char str[]){
	    perror(str);
	    exit(1);
}









//=============play asny==========

void *findasny(void *)
{
	while(true)
	{
         while(pr==pw)
		{
			if(frd==true) goto sx;
		}
		 int ptid=THREAD-1;
		
		 for(int i=0;i<iotemp[pr].len;i++)
		 {
			 if(iotemp[pr].buff[i]=='\n')
			 {     
                    while(bj[ptid]!=1)
					{ 
						if(ptid>0)
						{
							__sync_sub_and_fetch(&ptid,1);
					    }
						else __sync_add_and_fetch(&ptid,THREAD-1);
					}	
					__sync_sub_and_fetch(&bj[ptid],1);
					pthread_mutex_unlock(&flag[ptid]);

			 }
		 }
		 __sync_add_and_fetch(&pr,1);
		 
	}
sx:;


}



//================================
//=============io asny============
void *ioasny(void *)
{ 
    while(true)
	{
		while(pt==pw)
		{
			if(frd==true)
			{
                 fclose(file);	
			  //=======================time==================		
				gettimeofday(&endtime,0);
				unsigned long long timeuse  = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
				timeuse /=1000;        //除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时
				printf("count=%llu",timeuse);
				fflush(stdout);

                //============================================
				exit(0);
			}
		}
		
		fwrite(iotemp[pt].buff,iotemp[pt].len,1,file);
		__sync_add_and_fetch(&pt,1);
	
	}
    

}


//================================
//=======receve data==========
void *receive(void* arg)
{
	 int temp,len;
     iotemp=new IOS[10474544];

//	 cout<<"ioasny"<<endl;      
     
     pthread_create(&io_pid,NULL,ioasny,NULL);
//	 cout<<" io receive"<<endl;
	 c_client *ceve=(c_client *)arg;
	 while(true)
	 {
		 iotemp[pw].len=ceve->recv(iotemp[pw].buff,MAX);
		 if(iotemp[pw].len==0) 
		 {
		     __sync_add_and_fetch(&frd,1);
			 break;
		 }
		 __sync_add_and_fetch(&pw,1);
	 }
//	 cout<<"woca"<<endl;
	
	 
	 
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
          if(frd==true) break;
          pthread_mutex_lock(&flag[id]);
		  ceve->send("g",1);
		  __sync_add_and_fetch(&bj[id],1);
//		  cout<<id<<" bj "<<bj[id]<<endl;
		  	
//		  pthread_mutex_lock(&mutex);
//          q.push(id);

//		  pthread_mutex_unlock(&mutex);
	}
}
//====================================

//--------------------------------------------
int main(int ac,char *av[])
{
//=============time==================

       gettimeofday(&starttime,0);
//====================================
  
  



        if(ac!=4)
        {
			    oops("argument error");
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
	    pthread_create(&cev_pid,NULL,receive,&cev);
	    
//===========================
//===============ioasny===============
        if((file=fopen(av[3],"w"))==NULL)
			 oops("fwrite fail"); 



//====================================

// =======request thread pool=======
       c_client req(av[1],port); 
 

		for(int i=0;i<THREAD;i++)
	   {
		   pthread_create(&pid[i],NULL,request,&req);
	   }
	
//	   cout<<"ok"<<endl;
      
	  pthread_t fy_pid;
	  pthread_create(&fy_pid,NULL,findasny,NULL);
		
// =============================
//=============waite thread=====

//		pthread_join(cev_pid,NULL);
        pthread_join(io_pid,NULL);

 
		

         return 0;
}
