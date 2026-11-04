#include <stdio.h>
#include <unistd.h>

/* Print the process ID. */
int main()
{    
    printf("My process ID : [%d] \n", getpid());
    printf("My parent process ID : [%d] \n", getppid());
}
