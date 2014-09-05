#include "strplay.h"
using namespace std; 



NODE::NODE(DATA *t_data):num(0),data(t_data)
{
     

}


DATA::DATA(char path[])
{
    fd = open(path,O_RDONLY);
    xln = lseek(fd,0,SEEK_END); 
    buf = (char *) mmap(NULL,xln,PROT_READ,MAP_PRIVATE,fd,0);
	ptr=buf;
	end=buf+xln;
 
}

int NODE::make()
{
	int len=0;
    char *ps=data->ptr;
	if(ps==data->end) return -1;
	for(;ps!=data->end && *ps!='\n';++ps)
	{
                                                   //找出一个语句
    }
	
	++ps;
//	cout<<"/ntes:"<<*ps<<endl;
//	getchar();
	len=ps-(data->ptr);
    len=play(data->ptr,len);        //保存处理后的长度
	data->ptr=ps;
//	cout<<len<<endl;
    return len;
}

int NODE::play(char *str,int len)
{
		
	char *ps=ans;
	sprintf(ans,"%lld",num);
	while(*ps!=0)
	{
		++ps;
	}
//	 cout<<"ok:   "<<num<<" "<<ans<<" "<<len<<" "<<ps-ans<<"    "<<endl;
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
/*
//		cout<<"ko: "<<ps<<endl;
    if(num==219177 || num==219178 || num==219179 || num==219180){
	    
		 for(char *i=ans;i<=ps;++i)
		{
			 printf("%c",*i);
		}
		//cout<<endl;
//		getchar();
	}
*/
	++num;
	return ps-ans+1;
}
