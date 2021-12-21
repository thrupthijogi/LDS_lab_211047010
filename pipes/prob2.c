#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

int main(void) 
{
  int pipefds[2];
  char buffer[5][5];
  int matrix[2][2] = {{1,2},{3,4}};
  int transpose[2][2];
  int m = 2, n = 2;
  int i,j;
 
  if(pipe(pipefds) == -1) 
  {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
 
  pid_t pid = fork();
 
  if(pid == 0) 
  { // in child process
    
    close(pipefds[0]); // close read fd
    
   for (i = 0;i < m;i++)
      for (j = 0; j < n; j++)
         transpose[j][i] = matrix[i][j];
   printf("Transpose of the matrix:\n");
   for (i = 0; i< n; i++) {
      for (j = 0; j < m; j++)
         printf("%d\t", transpose[i][j]);
      printf("\n");
   }
   return 0;
    
    write(pipefds[1], transpose, 2*sizeof(int)); // write transpose matrix to pipe
 
    printf("writing transpose matrix into pipe \n");
    sleep(2); // intentional delay
    exit(EXIT_SUCCESS);
  }
 
  if(pid > 0) 
  { 
  // in parent process
    wait(NULL); // wait for child process to finish
    close(pipefds[1]); // close write fd
    read(pipefds[0], buffer, 4*sizeof(int)); // read PIN from pipe
    close(pipefds[0]); // close read fd
    printf("parent process printing \n");
    
    for (i = 0; i< n; i++) {
      for (j = 0; j < m; j++)
         printf("%d\t", buffer[i][j]);
      printf("\n");
   }
   
   
   printf("Reading transpose matrix from pipe \n");
    //sleep(2); // intentional delay
    exit(EXIT_SUCCESS);
    
  }
 
  return EXIT_SUCCESS;
}
