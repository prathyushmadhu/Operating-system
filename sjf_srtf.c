#include<stdio.h>
struct RQ{
    char pid[3];
    int at,bt,wt,rt,rest;
};

int main() {
    printf("Enter number of process: ");
    int n;
    scanf("%d",&n);
    struct RQ r[n];
    for(int i=0; i<n; i++) {
        printf("Enter pid: ");
        scanf("%s",r[i].pid);
        printf("ENTER ARRIVAL TIME : ");
        scanf("%d",&r[i].at);
        printf("ENTER BURST TIME : ");
        scanf("%d",&r[i].bt);

        r[i].rt = r[i].bt;
        r[i].wt = 0;
        r[i].rest = 0;

    }

    // Sort based on arrival time
    for(int i=0; i<n; i++) {
        for(int j=0; j< n-1; ) {
            if(r[j].at > r[j+1].at) {
                struct RQ temp = r[j];
                r[j]=r[j+1];
                r[j+1]=temp;
            }
        }
    }
    int count=0;
    int t=0;
    int avg_tat=0;
    int avg_rest=0;
    int avg_wt=0;

    // SJF non preemptive
    count=0;
    t=0;
    avg_wt = 0;
    avg_tat = 0;
    avg_rest = 0;
}