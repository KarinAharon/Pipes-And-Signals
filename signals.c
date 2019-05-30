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
int arr[5];
int pidIndex;

void sigCatcher(int sign){
      printf("PID %d caught one", arr[pidIndex]);
      kill(arr[pidIndex],SIGINT);
      exit(0);
}

int main(){

int p;
int i;

for (i= 0; i < 5; i++){
   p = fork();
  if(p < 0){  
    printf("Fork not successfull\n");  
    exit(0);
  }  
  if (p==0){
    signal(SIGINT, sigCatcher);	
    printf("PID %d is ready\n", getpid());
    //arr[i]=0;
    pidIndex=i;
    break;
  }
  else {
    arr[i]=p;
  }	
} 	
if(getpid()==arr[4])
	kill(arr[3],SIGINT);

for (int i = 0; i<5 ; i++){
	
	wait(NULL);
}






return 0;

}
