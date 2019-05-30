#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string> 
#include<sys/wait.h> 
#include<fcntl.h>
#include<sys/uio.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/fcntl.h>
#include "md5.h"

int flag=-1;
char recived_str[33];

void checkHashed(int sign);

int main() 
{ 
     std::string nsg;
  
    // We use two pipes: First pipe to send input string from parent, Second pipe to send concatenated string from child 
  
    int pipe1[2];  // Used to store two ends of first pipe 
    int pipe2[2];  // Used to store two ends of second pipe 
   
    pid_t p; 
  
    if (pipe(pipe1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        exit (1); 
    } 
    if (pipe(pipe2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        exit (1); 
    } 
    char input_str[20];
    
printf("plain text: ");
    scanf("%s", input_str); 

    p = fork(); 

  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        exit (1); 
    } 


    // Parent process 
    else if (p > 0) 
    { 
        signal(SIGINT,checkHashed);

        close(pipe1[0]);  // Close reading end of first pipe 
  
        // Write input string and close writing end of first 
        // pipe. 
        write(pipe1[1], input_str, strlen(input_str)+1); 
        close(pipe1[1]); 
  
        close(pipe2[1]); // Close writing end of second pipe 
                sleep(2);

        // Read string from child, print it and close 
        // reading end. 
        read(pipe2[0], recived_str, 33);
        close(pipe2[0]); 

        if(flag==0){
        printf("encrypted by process %d: %s",getpid(),recived_str);
        kill(p,SIGTERM);
        }
        wait(NULL);
    } 
  
    // child process 
    else
    { 
        close(pipe1[1]);  // Close writing end of first pipe 
  
        // Read a string using first pipe 
        //char str[20]; 
        read(pipe1[0], recived_str, 20); 
        nsg=md5(recived_str);
        // Close oth reading ends 
        close(pipe1[0]); 
        close(pipe2[0]); 
        sleep(3);
        // Write concatenated string and close writing end 
      write(pipe2[1], nsg.c_str(),32);
      close(pipe2[1]); 
      kill(getppid(),SIGINT);
      for(;;){sleep(2);};//so that the child will not be a zombie
      exit(0); 
    } 
}
void checkHashed(int sign){
  int length=strlen(recived_str);
  if(length==32) flag= 0;
  else flag= -1;
}
