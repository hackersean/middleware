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
	len=ps-(data->ptr);
    len=play(data->ptr,len);        //保存处理后的长度
	data->ptr=ps;
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
	int tp=len-2;
	int t=tp/3;
	int w=t*2;

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
	++num;
	return ps-ans+1;
}
