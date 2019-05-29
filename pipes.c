#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<wait.h>
#include<signal.h>
#include<sys/wait.h>
#include "md5.h"

//
// USING https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/ at source
//

size_t current_size;
char * print_that;

void signal_handler(int signo){
  if(signo == SIGINT && current_size == 32){
  printf("\nMD5 function success,The hash code (answer) for the input is : \n%s\n",print_that);
  kill(0,SIGKILL); // father process kill his children
  exit(1);
 }
 else{
   exit(0);
 }
}


int main(){ // all the process
    // We use two pipes
    // First pipe to send input string from parent - pipe1
    // Second pipe to send concatenated string from child - pipe2
// kill and catch the signal
    int pipe1[2];  // Used to store two ends of first pipe
    int pipe2[2];  // Used to store two ends of second pipe

    pid_t pid; // to know if it's the father or the child , present the PID of the process

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1){
        printf("%s","Pipe Failed" );
         exit (0);
    }

   pid = fork(); // create a process

   if (pid < 0){
       printf("%s","fork Failed" );
       return 1;
   }

   // Parent process
   else if (pid > 0)
   {
     close(pipe1[0]);
     char * temp;
     printf("Write your choose to check please : ");
     fgets(temp,20,stdin);
     write(pipe1[1],temp, strlen(temp) + 1); // send to the child, 3 = strlen(pipe1) + 1 , it's variable known
     close(pipe1[1]); // Close writing end of second pipe , this happend before the arrived of the massage
     sleep(1); // wait to the child active finish(active contains signal call)
     char * input_f_c;
     read(pipe2[0], input_f_c, 128); // read the answer from the child , true || false
     close(pipe1[0]);
     // this next 2 lines present the global variables for the out main function
     current_size = strlen(input_f_c);
     print_that = input_f_c;
     //
     kill(pid,SIGINT);
     // catch the signal
     signal_handler(SIGINT);
     exit(0);
    }

   // child process
   else
   {
       wait(NULL); // wait for the massage from father process
       // close(pipe1[1]);  // Close writing end of first pipe
       // Read a string using first pipe
       char input_f_f[32];
       read(pipe1[0], input_f_f, 32);
       // change the input to hash code
       std::string hash; // length = 32
       hash = md5(input_f_f);
       // change to char *
       char answer[hash.length() + 1];
       strcpy(answer, hash.c_str());
       //
       write(pipe2[1],answer,strlen(answer) + 1);
       close(pipe2[1]);
       // throw a signal
       signal(SIGINT,signal_handler);
       wait(NULL);
   }
   return 0;
} // end main()
