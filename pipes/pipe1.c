#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void) {
  int pipefds[2];
  char *pin, *pin1;
  char buffer[10];
 
  if(pipe(pipefds) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
 
  pid_t pid = fork();
 
  if(pid == 0) { // in child process
  
	int num, original, rem, sum = 0;
	//rem is remainder and original is the original number
	printf("Enter a three-digit Number: ");
	scanf("%d", &num);
	original = num;
	while(original != 0)
	{
		rem = original%10;
		sum =sum + rem*rem*rem;
		original=original/ 10;
	}
  	
  	sprintf(pin1, "%d", original);
  	
  	
	if(sum == num){
		pin = "yes\0"; // PIN to send
	    	close(pipefds[0]); // close read fd
	    	write(pipefds[1], pin, sizeof(pin)); // write PIN to pipe
	    	write(pipefds[1], pin1, sizeof(pin1)); 
	}else{
		pin = "no\0"; // PIN to send
	    	close(pipefds[0]); // close read fd
	    	write(pipefds[1], pin, sizeof(pin)); // write PIN to pipe
	    	write(pipefds[1], sum, sizeof(sum));
	
	}
  
    /*pin = "4821\0"; // PIN to send
    close(pipefds[0]); // close read fd
    write(pipefds[1], pin, 5); // write PIN to pipe*/
 
    printf("Generating PIN in child and sending to parent...\n");
    sleep(2); // intentional delay
    exit(EXIT_SUCCESS);
  }
 
  if(pid > 0) { // in main process
  
    
    
      
    wait(NULL); // wait for child process to finish
    close(pipefds[1]); // close write fd
    read(pipefds[0], buffer, sizeof(buffer)); // read PIN from pipe
    close(pipefds[0]); // close read fd
 
    printf("Parent received PIN '%s'\n", buffer);
  }
 
  return EXIT_SUCCESS;
}
