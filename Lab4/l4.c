#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//DEFIINE MEMORY
#define MEMORY 1024
int memory = MEMORY;
int printers = 2;
int scanners = 1;
int modems = 1;
int cds = 1;






struct process{
int time;
int priority;
int proctime;
int mb;
int numprinters;
int numscanners;
int nummodems;
int numcds;
}process;

struct queue{
    struct process current;
    struct queue *next;
} queue;


struct process prcs[100];
struct process rtp[100];
struct process p1[100];
struct process p2[100];
struct process p3[100];
int rtCount = 0;
int p1Count = 0;
int p2Count = 0;
int p3Count = 0;

void runTask(struct process proc){
  
printf("\nReady to run.");
memory = memory - proc.mb;
printers = printers - proc.numprinters;
scanners = scanners - proc.numscanners;
modems = modems - proc.nummodems;
cds = cds - proc.numcds;

for (int i = 0; i < proc.proctime; i++){
    printf("\nRunning...");
}

printf("\nRun Succesful.");

//RESET RESOURCES
 memory = MEMORY;
 printers = 2;
scanners = 1;
 modems = 1;
 cds = 1;


}

void push(){
int t1;
pthread_t thread;

printf("\n-----------------------");
//PUSH ALL REAL-TIME TASKS
printf("\nREAL-TIME TASKS: ");
printf("\nThere are %d tasks to be executed.", rtCount);
printf("\n");
for (int i = 0; i < rtCount; i++){
    runTask(rtp[i]);
}
printf("\n-----------------------");
printf("\n1st PRIORITY TASKS: ");
printf("\nThere are %d tasks to be executed.", p1Count);
printf("\n");
//PUSH ALL P1 TASKS
for (int i = 0; i < p1Count; i++){
    runTask(p1[i]);
}
printf("\n-----------------------");
printf("\n2nd PRIORITY TASKS: ");
printf("\nThere are %d tasks to be executed.", p2Count);
printf("\n");
//PUSH ALL P2 TASKS
for (int i = 0; i < p2Count; i++){
    runTask(p2[i]);
}
printf("\n-----------------------");
printf("\n3rd PRIORITY TASKS: ");
printf("\nThere are %d tasks to be executed.", p3Count);
printf("\n");
//PUSH ALL P3 TASKS
for (int i = 0; i < p3Count; i++){
    runTask(p3[i]);
}



}

void sort(struct process prcs){

    //SORT OUT TASKS BY PRIORITY
    if(prcs.priority == 0){
    rtp[rtCount] = prcs;
    rtCount++;
    printf("\nThis is a REAL-TIME task.");
}

  else if(prcs.priority == 1){
    p1[p1Count] = prcs;
    p1Count++;
    printf("\nThis is a P1 task.");
}
  else if(prcs.priority == 2){
    p2[p2Count] = prcs;
    p2Count++;
    printf("\nThis is a P2 task.");
}
else if(prcs.priority == 3){
    p2[p2Count] = prcs;
    p2Count++;
    printf("\nThis is a P2 task.");
}

}



int main(){



//OPEN DISPATCH LIST

FILE *file;
file = fopen("dispatchlist", "r");

if(file==NULL){
    printf("ERROR OPENING FILE.");
    exit(1);
}


char c[100];
char* token;

int i = 1;
int counter = 0;


//LOAD FATA INTO STRUCT
while (fgets(c, sizeof(c), file)){
    token = strtok(c, ",");
while (token != NULL){
if (i==1){
    prcs[counter].time = atoi(token);
    i++;
}
else if (i==2){
    prcs[counter].priority = atoi(token);
    i++;
}
else if(i==3){
    prcs[counter].proctime = atoi(token);
    i++;
}
else if(i==4){
    prcs[counter].mb = atoi(token);
    i++;
}
else if(i==5){
    prcs[counter].numprinters = atoi(token);
    i++;
}
else if(i==6){
    prcs[counter].numscanners = atoi(token);
    i++;
}
else if(i==7){
    prcs[counter].nummodems = atoi(token);
    i++;
}
else if(i==8){
    prcs[counter].numcds = atoi(token);
    i++;
}
token = strtok(NULL, ",");

}
i = 1;


//SEND TO SORT
sort(prcs[counter]);
counter++;


}

//PUSH TO QUEUE
push();

    return 0;
}