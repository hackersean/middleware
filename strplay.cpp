#include "strplay.h"
using namespace std; 



NODE::NODE(DATA *t_data):num(0),data(t_data)
{
     

}


DATA::DATA(char path[]):ptr(0)
{
    fd = open(path,O_RDONLY);
    xln = lseek(fd,0,SEEK_END); 
	
    buf = (char *) mmap(NULL,xln,PROT_READ,MAP_PRIVATE,fd,0);
 
	end=buf+xln;
 
}

LL NODE::make()
{
	LL len=0;
    char *ps=data->ptr;
	if(ps==data->end) return -1;
	for(;ps<data->end && *ps!='\n';++ps)
	{
        
    }
	ps+=2;
	len=ps-(data->ptr);
    play(data->ptr,len);
	data->ptr=ps;
    return len;
}

void NODE::play(char *str,LL len)
{
		
	LL ps=0;
	sprintf(ans,"%lld",num);
	while(ans[ps]!=0)
	{
		++ps;
	}
//		                  cout<<"ok:   "<<num<<" "<<ans<<" "<<len<<" "<<ps<<endl;
	LL tp=len-2;
	LL t=tp/3;
	LL w=t*2;
//       cout<<t<<" "<<w<<endl;
	for(LL i=tp-1;i>=w;--i,++ps)
	{
		ans[ps]=str[i];
	}
	for(LL i=t-1;i>=0;--i,++ps)
	{
		ans[ps]=str[i];
	}

	ans[ps]='\r';
	ans[++ps]='\n';
	++ps;
//		cout<<"ko: "<<ps<<endl;
	cout<<ans;
	++num;
}
