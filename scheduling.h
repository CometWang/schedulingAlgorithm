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

}queues[SIZE], backup[SIZE];
int readfromfile();