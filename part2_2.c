#include <stdio.h>
#include "scheduling.h"
#include <stdlib.h>


float avgwaitingtime(int array[], int processnum){
    int sum=0;
    float avgwaitingtime;
    for(int i=1; i<=processnum; i++){
        sum = sum + array[i];
      //  printf("%d\n", array[i]);
    }
    avgwaitingtime = (float)sum/(processnum);
    return avgwaitingtime;

}

int * fcfs(struct queue newque){
    //it will return an array of waiting time in the excatlly same index
    // of that the process order is in the input file

    int sum=0, number;
    number = newque.processnum;
    int *waitingt = (int*) malloc(number* sizeof(int));

    waitingt[1]=0;
    for(int i=2; i<= number; i++) {
        sum += newque.statistic[i - 1];
        waitingt[i] = sum;
    }


    return waitingt;

}

struct queue sjf(struct queue old){
    char *exchange;
    int num=old.processnum, tmp;
    //sort the burst time in the old queue and switch the corresponding process number at the same time
    //also put them into the new queue struct
    for(int i=1; i<num; i++){
        for(int j=1; j<num; j++){
            if(old.statistic[j]>old.statistic[j+1]){
                tmp=old.statistic[j];
                exchange =old.processinfor[j];
                old.processinfor[j]=old.processinfor[j+1];
                old.processinfor[j+1]=exchange;
                old.statistic[j]=old.statistic[j+1];
                old.statistic[j+1] = tmp;

            }
        }
    }
    return old;
}

struct queue roundrobin(struct queue old){
    //change the struct of old queue into the one with new sequence of both processes and burst time
    int amount = old.processnum;
    int tq= old.tqnum, count=0;

    char *tmp;
    for(int i=1; old.statistic[i]!=NULL; i++){
        if(old.statistic[i]>tq){
            count +=1;
            old.statistic[amount+count] = old.statistic[i]-tq;
            old.processinfor[amount+count]= old.processinfor[i];
            old.statistic[i] = tq;

        }
    }
    //old.processnum = amount+count;
    return old;

}

struct queue *turnaroundtime(struct queue old){
    //calculate turnaround time for each process

    struct queue *new;
    new = (struct queue*) malloc(1 * sizeof(struct queue));
    for(int i=1; i<=old.processnum; i++){
        int time=old.statistic[i];
        int last=i;

        for(int j=i+1; old.processinfor[j]!=NULL; j++){
            if(old.processinfor[j] == old.processinfor[last]){
                int tmp=j;
                for(tmp;tmp>last;tmp--){
                time = time + old.statistic[tmp];
                }
                last=j;

            }

        }
        new->statistic[i]= time;
        new->processinfor[i]=old.processinfor[i];

    }
    int index =1;
    for(int i =1; old.processinfor[i]!=NULL; i++){
        char * compare=old.processinfor[i];

        for(int j =i+1; ; j++) {
            if (old.processinfor[j] == compare) {
                break;
            }
            if(old.processinfor[j]!=compare&&old.processinfor[j+1]==NULL){
                new->backupprocess[index]=old.processinfor[i];
                index++;
                break;
            }
        }

    }
    for(int j=1; new->backupprocess[j]!=NULL; j++){
        for(int i=1; new->processinfor[i]!=NULL; i++){
            if(new->processinfor[i]==new->backupprocess[j]){
                new->backuptime[j]=new->statistic[i];

            }
        }
    }

    return new;

}

int main(){

    int row = readfromfile();
   // FILE* fpwrite=fopen("/Users/apple/CLionProjects/3305ass2/cpu_scheduling_output_file.txt","w");
    FILE* fpwrite=fopen("cpu_scheduling_output_file.txt","w");
    if(fpwrite ==NULL){
        //fail to open the file
        printf("can't open the file to write!");
        return -1;
    }

    for(int i =1; i<=row; i++){

        int pamount=queues[i].processnum;
        int *p ;

        //***********write information of FCFS***********

        fprintf(fpwrite, "\nReady Queue %d Applying FCFS Scheduling:\n",queues[i].id);
        fprintf(fpwrite, "\nOrder of selection by CPU:\n");
        for(int j=1; j<=queues[i].processnum; j++){
            fprintf(fpwrite, "%s ",queues[i].processinfor[j]);
        }
        fprintf(fpwrite,"\n\nIndividual waiting times for each process: \n");
        p = fcfs(queues[i]);
        for(int j=1; j<=pamount; j++){
            fprintf(fpwrite, "%s = %d\n", queues[i].processinfor[j], *(p+j));
        }
        fprintf(fpwrite, "\nAverage waiting time = %.1f\n", avgwaitingtime(p, pamount));
        free(p);

        // *************write information for SJF************

        struct queue new= sjf(queues[i]);
        fprintf(fpwrite, "\nReady Queue %d Applying SJF Scheduling:\n \nOrder of selection by CPU\n", queues[i].id);
        for(int j=1; j<=queues[i].processnum;j++){
            fprintf(fpwrite,"%s ", new.processinfor[j]);
        }
        fprintf(fpwrite,"\n\nIndividual waiting times for each process: \n");
        p = fcfs(new);
        for(int j=1; j<=pamount; j++){
            fprintf(fpwrite,"%s = %d\n", new.processinfor[j], *(p+j));
        }
        fprintf(fpwrite,"\nAverage waiting time = %.1f\n", avgwaitingtime(p, pamount));
        free(p);

        //***********write information for RR**************

        struct queue rr= roundrobin(queues[i]);
        fprintf(fpwrite,"\nReady Queue %d Applying RR Scheduling:\n \nOrder of selection by CPU\n", queues[i].id);
        for(int j=1; rr.processinfor[j]!= NULL;j++){
            fprintf(fpwrite,"%s ", rr.processinfor[j]);
        }
        struct queue *newrr;

        newrr= turnaroundtime(rr);
        fprintf(fpwrite,"\n\nTurnaround times for each process:\n" );
        for(int i=1; newrr->backupprocess[i]!=NULL;i++){
            fprintf(fpwrite, "%s = %d\n", newrr->backupprocess[i], newrr->backuptime[i]);

        }

        //initialize the temporaries struct
        for(int j=1; rr.processinfor[j]!= NULL;j++){
            rr.processinfor[j]=NULL;
            rr.statistic[j]=NULL;
        }
        for(int i=1; newrr->backupprocess[i]!=NULL;i++){
            newrr->backupprocess[i]=NULL;
            newrr->backuptime[i]=NULL;

        }
        //free(newrr);

    }
    fclose(fpwrite);

    return 0;


}
