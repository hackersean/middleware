#include "strplay.h"
using namespace std;
#define LL long long
#define BUFFER 300
struct NODE
{
	 static LL num;
     char str[BUFFER];
	 char ans[BUFFER];
     void play()
	{
		
		int len(strlen(str)),ps=0;
        sprintf(ans,"%lld",num);
        while(ans[ps]!=0)
		{
			++ps;
		}
//		                  cout<<"ok:   "<<num<<" "<<ans<<" "<<len<<" "<<ps<<endl;
		int tp=len-2;
        int t=tp/3;
		int w=t*2;
//       cout<<t<<" "<<w<<endl;
		for(int i=tp-1;i>=w;--i,++ps)
		{
            ans[ps]=str[i];
		}
		for(int i=t-1;i>=0;--i,++ps)
		{
			ans[ps]=str[i];
		}

		ans[ps]='\r';
		ans[++ps]='\n';
		ans[++ps]=0;
		++ps;
//		cout<<"ko: "<<ps<<endl;
		cout<<ans;
		++num;
	}
};
