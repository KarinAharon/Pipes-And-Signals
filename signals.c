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


void sigCatcher(int sign);

int main(){

int p;
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
  else arr[i]=p;
  	
} 	
 sleep(2);
 kill(arr[4],SIGINT);
 int Zchild;
 sleep(2);

for (int i = 0; i<5 ; i++){
	Zchild = wait(NULL);
	printf("Process %d is dead\n", Zchild);
	kill(Zchild,SIGTERM);
}






exit(0);

}
void sigCatcher(int sign){
      printf("PID %d caught one\n", getpid());
      if(pidIndex>=0) kill(arr[pidIndex],SIGINT);
}
