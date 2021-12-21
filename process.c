#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
int main( ){
   pid_t child_pid;
int i,number,fact=1;
   child_pid = fork (); // Create a new child process;
   if (child_pid < 0) {
      printf("fork failed");
      return 1;
   } else if (child_pid == 0) {
      printf("enter a number\n");
   scanf("%d",&number);
for(i=1;i<=number;i++)
{
fact=fact*i;
}
printf("facorial of %d is %d\n",number,fact);
   } else {
      wait(NULL);
if(number%2==0)
printf("%d is even\n",number);
else
printf("number is not even\n");
      printf ("parent process successfully created!\n");
      printf ("child_PID = %d, parent_PID = %d", getpid( ), getppid( ) );
   }
   return 0;
}
