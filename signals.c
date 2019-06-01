#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<fcntl.h>
#include<sys/uio.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/fcntl.h>

int arr[5];
int pidIndex;
int p;

void sigCatcher(int sign);
void killAll(int sign);

int main(){


int i;


for (i= 0; i < 5; i++){
  p = fork();
  if(p < 0){
    printf("Fork was not successfull\n");
    exit(0);
  }
  if (p==0){
    signal(SIGINT, sigCatcher); 
    printf("PID %d is ready\n", getpid());
    pidIndex=i-1;
    pause();
    exit(0);
  }
  else { 
        signal(SIGINT, killAll);        
        arr[i]=p;
  }     
}       

sleep(1);
   kill(arr[4],SIGINT);
 pause();
 exit(0);

}

void killAll(int sign){
     for (int i = 0; i<5 ; i++)
        if(kill(arr[i], SIGKILL)==0)
           printf("Process %d is dead\n", arr[i]);
}

void sigCatcher(int sign){
      printf("PID %d caught one\n", getpid());
      if(pidIndex>=0) kill(arr[pidIndex],SIGINT);
      if(pidIndex==-1) kill(getppid(), SIGINT);
}
