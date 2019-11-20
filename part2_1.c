
#include <stdio.h>
#include <stdlib.h>
#define SIZE 255

struct queue{
    int id;// queue number
    int tqnum;// tq
    int staticsnum;//total amount of statistics of each queue
    int processnum;//total process amount of each queue
    char *information[SIZE][SIZE];//buf to store each line from the file

    char *processinfor[SIZE];//the arrival order
    int statistic[SIZE];//each process's CPU burst time
    int backuptime[SIZE];//for rr algorithm use
    char *backupprocess[SIZE];// for rr algorithm

}queues[SIZE];


int readfromfile(){

    //int** array;
    int n = 0, flag = 0, row = 0;

    FILE *fp = fopen("cpu_scheduling_input_file.txt", "r");
    //FILE *fp = fopen("/Users/apple/CLionProjects/3305ass2/cpu_scheduling_input_file.txt", "r");
    if (fp == NULL) {
        printf("Can't open the file");
        exit(0);
    }

    //get the number of rows in the file
    while (!feof(fp)) {
        flag = fgetc(fp);
        if (flag == '\n')
            n++;
    }
    row = n + 1;

    rewind(fp);
    int c=0;

    for(int i =1; i <=row; i++) {
        for (int j = 0;; j++) {
            if ((fscanf(fp, "%s", &queues[i].information[j]) != EOF)) {

                if (c = fgetc(fp) == '\n') {

                    //get information from the queues
                    queues[i].staticsnum = j + 1; //total amount of stat in each line
                    queues[i].processnum = (j-3)/2; // total amount of processes in each queue
                    queues[i].tqnum = atoi(queues[i].information[3]);
                    queues[i].id = atoi(queues[i].information[1]);

                    queues[i].statistic[0]=0;
                    //store the process time into the statistic array
                    for (int k = 1, m = 5; m <= queues[i].staticsnum; m++) {

                        queues[i].statistic[k] = atoi(queues[i].information[m]);

                        m++;
                        k++;
                    }

                    //store the process sequence(same index as process time)
                    for (int g = 1, n = 4; n < queues[i].staticsnum; n++) {
                        char *new = queues[i].information[n];
                        queues[i].processinfor[g] = new;
                        //printf("the process sequence is : %s\n", queues[i].processinfor[g]);
                        n++;
                        g++;
                    }

                    break;
                }
            } else {//for the last queue in the file
                //get information from the queues
                queues[i].staticsnum = j;
                queues[i].processnum = (j-4)/2;
                queues[i].statistic[0]=0;

                queues[i].tqnum = atoi(queues[i].information[3]);
                queues[i].id = atoi(queues[i].information[1]);

                //store the process time into the statistic array
                for (int k = 1, m = 5; m <=queues[i].staticsnum; m++) {

                    queues[i].statistic[k] = atoi(queues[i].information[m]);
                    //printf("the stat k:%d for each process is:%d\n", k, queues[i].statistic[k]);
                    m++;
                    k++;
                }

                //store the process sequence(same index as process time)
                for (int g = 1, n = 4; n < queues[i].staticsnum; n++) {
                    char *new = queues[i].information[n];
                    queues[i].processinfor[g] = new;
                    //printf("the process g : %dsequence is : %s\n",g, queues[i].processinfor[g]);
                    n++;
                    g++;

                }

                break;
            }
        }
    }
        fclose(fp);
        return row;

}
