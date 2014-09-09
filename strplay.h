#ifndef __SDATA__
#define __SDATA__

#include "config.h"
using namespace std;


inline void oops(char str[]){
	    perror(str);
	    exit(1);
}

struct NODE
{
	 LL num;
	 char *ps;
     char str[BUFFER];
	 char ans[BUFFER];
     
	int play()
	{
		ps=ans;
		int len(strlen(str));
		ps=ans+sprintf(ans,"%lld",num);
	
//			                  cout<<"ok:   "<<num<<" "<<ans<<" "<<len<<" "<<ps<<endl;
		int tp=len-2;
		int t=tp/3;
		int w=t*2;
	//       cout<<t<<" "<<w<<endl;
		for(int i=tp-1;i>=w;--i,++ps)
		{
			*ps=str[i];
		}
		for(int i=t-1;i>=0;--i,++ps)
		{
			*ps=str[i];
		}

		*ps='\r';
		*++ps='\n';
		*++ps=0;
	//		cout<<"ko: "<<ps<<endl;
	//		cout<<ans;
		++num;
		return ps-ans;
	}
	 NODE():num(0){}
};


struct DATA
{
	FILE* fp;                  //注意
	DATA(char *path)
	{
		if((fp=fopen(path,"r"))!=NULL)
		{
			
		}
		else
		{
			oops("数据文件打开失败");
		}
    }    
};

void read_data(DATA &data);



#endif
