/*Implement a c prog using pipes, the child process checks the given number is an armstrong number.
If it is, child process writes "yes" to the pipe. Parent process reads the result .
If yes, parent process checks whether armstrong number is a palindrome, if "no", prints sum of the armstrong number.
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

  int main(void) {
  int pipefds[2];
  
  int n;
  printf("Enter a three-digit Number: ");
	scanf("%d", &n);
  int r,sum=0,temp;  
  char buffer[5];
 
  if(pipe(pipefds) == -1) 
  {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
 
  pid_t pid = fork();
 
  if(pid == 0) 
  { // in child process
    
    temp=n;    
    while(n>0)    
    {    
        r=n%10;    
        sum=sum+(r*r*r);    
        n=n/10;    
    }    
    if(temp==sum)
    {    
        printf("child process writing 'yes' to the pipe \n");
        write(pipefds[1], "yes", sizeof("yes"));
    }
            
    else 
    {   
        printf("child process writing 'no' to the pipe \n"); 
        write(pipefds[1], "no", sizeof("no"));
    }
          
    return 0;  
    
    close(pipefds[0]); // close read fd
    sleep(2); // intentional delay
    exit(EXIT_SUCCESS);
  }
 
  if(pid > 0) 
  { 
  // in parent process
    char str1[] = "yes";
    char str2[] = "no";
    
    wait(NULL); // wait for child process to finish
    close(pipefds[1]); // close write fd
    printf("parent process writing \t");
    
    read(pipefds[0], buffer, 5);
    
    if (strcmp(str1, buffer) == 0)
    {
        
        printf("Armstrong number\n");
      
        int r,sum=0,temp;      
        temp=n;    
        while(n>0)    
        {    
            r=n%10;    
            sum=(sum*10)+r;    
            n=n/10;    
        }    
        if(temp==sum)    
            printf("palindrome number \n");    
        else    
            printf("not palindrome \n");   
        return 0;
    }  
   else
   {
      printf("not Armstrong number\n" );
      
        int sum=0,m;      
        while(n>0)    
        {    
            m=n%10;    
            sum=sum+m;    
            n=n/10;    
        }    
        printf("Sum of digits in Armstrong number is =%d \n",sum);    
        return 0;  
   }
    
    return 0; 
    close(pipefds[0]); // close read fd
 
    
 }
 
  return EXIT_SUCCESS;
}
