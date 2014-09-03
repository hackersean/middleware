#include "socklib.h"
using namespace std;
int main(int ac,char *av[])
{
        if(ac!=3)
        {
			    perror("argument error");
		} 
		
		c_client client(av[1],av[1]);
		
		
         return 0;
}
