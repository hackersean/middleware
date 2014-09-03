#include "socklib.h"
using namespace std;
int main(int ac,char *av[])
{
        if(ac!=2)
        {
			    perror("argument error");
		} 
		
		c_serve serve(atoi(av[1]));
		
		
		
         return 0;
}
