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

void sigCatcher(int sign){
      printf("PID %d caught one\n", arr[pidIndex]);
       if(pidIndex>=0) kill(arr[pidIndex],SIGINT);
      exit(0);
}

int main(){

int p;
int i;
signal(SIGINT, sigCatcher);	

for (i= 0; i < 5; i++){
  p = fork();
  if(p < 0){  
    printf("Fork not successfull\n");  
    exit(0);
  }  
  if (p==0){
    printf("PID %d is ready\n", getpid());

    //arr[i]=0;
    pidIndex=i-1;
    pause();
    exit(0);
  }
  else {
    arr[i]=p;
  }	
} 	
  sleep(3);
 kill(arr[4],SIGINT);

int state;
  sleep(3);
for (int i = 0; i<5 ; i++){
	int Zchild = wait(&state);
	printf("process %d is dead\n", Zchild);
	kill(Zchild,SIGTERM);
}






exit(0);

}
