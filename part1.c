#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<pthread.h>


int sum=0;
int *newfunction(void *num){
    //for the calculation of sum during thread

      int *numadd = (int*) num;
      //int thread_id;
      sum += *numadd;
      if(*numadd == 20){

          pthread_exit(sum);
      }

}


int main() {

    int x=10, y=20, z=0, fd[2];
    pid_t  pid;

    if(pipe(fd)<0){//if pipe is not successful
        printf("pipe failed!");
        exit(0);

    }
    pid=fork();
    if(pid < 0){//if fork is not successful
        printf("Unsuccessful fork!");
        exit(0);
    }

    if(pid > 0){
        //parent process
        wait(NULL);
        //read(fd[0], &c, 4);
        printf("The z value from parent process is %d\n", z);
        pthread_t thread_1;
        pthread_t thread_2;
        pthread_create(&thread_1, NULL, newfunction, &x);
        pthread_create(&thread_2, NULL, newfunction, &y);
        pthread_join(thread_1, NULL);
        pthread_join(thread_2, NULL);
        printf("The z value from thread is %d\n", sum);

    }

    if(pid ==0){//child process
        z = x +y;
        //write z into the pipe
        //write(fd[1], &z, 4);

    }
    return 0;

}