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


int main() 
{ 
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
	printf("Please enter a string");
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
  	
        close(pipe1[0]);  // Close reading end of first pipe 
  
        // Write input string and close writing end of first 
        // pipe. 
        write(pipe1[1], input_str, 21); 
        close(pipe1[1]); 
  
        // Wait for child to send a string 
        wait(NULL); 
  
        close(pipe2[1]); // Close writing end of second pipe 
  
        // Read string from child, print it and close 
        // reading end. 
    //   read(pipe2[0], recived_str, 20); 
        close(pipe2[0]); 
    } 
  
    // child process 
    else
    { 
        close(pipe1[1]);  // Close writing end of first pipe 
  
        // Read a string using first pipe 
       // char recived_str[20]; 
        //read(pipe1[0], recived_str, 20); 
	//string res = md5(recived_str);

   

        // Close both reading ends 
        close(pipe1[0]); 
        close(pipe2[0]); 
  
        // Write concatenated string and close writing end 
      //  write(pipe2[1], digest, strlen(res)+1); 
        close(pipe2[1]); 
  
        exit(0); 
    } 
}
