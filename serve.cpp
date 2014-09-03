#include "socklib.h"
using namespace std;

void data_transfer(int fd)
{
	      int n=20;
          while(n)
          {
			    cout<<n<<endl;
			     if(send(fd,"great",6,0))
			     {
					     sleep(1);
				  }
			       --n;
		  }
}

int main(int ac,char *av[])
{
        if(ac!=2)
        {
			    perror("argument error");
		} 
		 
		c_serve serve(atoi(av[1]));

		 data_transfer(serve.accept());
		 
		cout<<"end"<<endl;
		
		
		
         return 0;
}
