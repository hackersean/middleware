#include "socklib.h"

#define MAX 4096
#define THREAD 48

char buff[MAX];
int pt=0,pw=0;
struct IOS
{
    char buff[MAX];
	int len;
};

IOS *iotemp;
FILE *file;

static int count=THREAD;                     //request count

timeval starttime;
timeval endtime; 

pthread_t pid[THREAD];
bool bj[THREAD];
pthread_mutex_t flag[THREAD];
<<<<<<< HEAD
//queue <int> q;
=======
queue <int> q;
>>>>>>> 3bbd85e35321203d1767bb06f1bfe279bfb9943a
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;



inline void oops(char str[]){
	    perror(str);
	    exit(1);
}

//=======receve data==========
void *receive(void* arg)
{
	 int tp,len;
     iotemp=new IOS[10474544];
	 
	 c_client *ceve=(c_client *)arg;
	 while(true)
	 {
		 len=ceve->recv(buff,MAX);
		 tp=pw;
//		 __sync_add_and_fetch(&pw,1);
//		 cout<<"rea "<<pt<<" "<<pw<<endl;
//		 cout<<len<<endl;
		 if(len==0) 
		 {
			 //=========timer========================
		     
			 break;
		 }
		 int ptid=THREAD-1;
		
		 for(int i=0;i<len;i++)
		 {
			 if(buff[i]=='\n')
			 {     //cout<<ptid<<" xxx "<<bj[ptid]<<endl;
//                pthread_mutex_lock(&mutex);
                //if(q.empty()!=true)
				
//					cout<<"unlock "<<q.front()<<" "<<q.size()<<endl;
                    while(bj[ptid]!=1)
					{//cout<<ptid<<" "<<bj[ptid]<<endl;
						if(ptid>0)
						{
							__sync_sub_and_fetch(&ptid,1);
					    }
						else __sync_add_and_fetch(&ptid,THREAD-1);
					}	
					//cout<<ptid<<endl;
					__sync_sub_and_fetch(&bj[ptid],1);
//					cout<<ptid<<" rec "<<bj[ptid]<<endl;
					pthread_mutex_unlock(&flag[ptid]);
//					q.pop();
			    
				
//				pthread_mutex_unlock(&mutex);
			 }
		 }
//		 cout<<"rec "<<pt<<" "<<pw<<endl;
//		 __sync_add_and_fetch(&pt,1);
		 fwrite(buff,len,1,file);
	 }
//	 cout<<"woca"<<endl;
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
        if((file=fopen(av[3],"w"))==NULL)
			 oops("fwrite fail"); 
	    
	    pthread_create(&cev_pid,NULL,receive,&cev);
	    
//===========================
//===============ioasny===============
       

//====================================

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


		gettimeofday(&endtime,0);
		unsigned long long timeuse  = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
		timeuse /=1000;        //除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时
		printf("count=%llu\n",timeuse);
			 
		
<<<<<<< HEAD
=======
		
//=======================time==================		
        gettimeofday(&endtime,0);
        unsigned long long timeuse  = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
        timeuse /=1000;        //除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时
        printf("count=%llu",timeuse);
		fflush(stdout);

 //============================================
>>>>>>> 3bbd85e35321203d1767bb06f1bfe279bfb9943a
         return 0;
}
