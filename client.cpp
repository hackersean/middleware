#include "socklib.h"
#define MAX 1000000
char buff[M_BUFFER];
char info[]="sta\0safasdft\r";

//function

inline void oops(char str[]){
	    perror(str);
	    exit(1);
}


void writefile(FILE *file,c_client &ceve)
{
	 int x;
	 while(true)
	 {
		 ceve.send(info);
		 x=ceve.recv(buff);
		 if(x==0) break;
		 fwrite(buff,x,1,file);
	 }
	 fclose(file);
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

		FILE *file;
		if((file=fopen(av[3],"w"))==NULL)
			oops("fwrite fail");
		
        writefile(file,ceve);
		
			   
		
         return 0;
}
