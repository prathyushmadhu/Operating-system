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
        r[i].rt = r[i].bt;  // Remaining time
        r[i].wt = 0; 
        r[i].rest = 0;  // response time
    }

    // Sort based on arrival time
    for(int i=0; i<n; i++) {
        for(int j=0; j< n-1; j++) {
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
    int smallest_bt = 0;
    printf("\nSJF NON PREEMPTIVE SCHEDULING\nGANTT CHART\n|0|\t");
    while(count < n) {
        for(int j=0; j<n; j++) {
            if((r[j].at <= t)&&(r[j].rt > 0)) {
                smallest_bt = j;
                break;
            }
        }
        
        for(int j=0; j<n; j++) {
            if((r[j].at <= t) && (r[j].rt < r[smallest_bt].bt)&&(r[j].rt>0)) {
                smallest_bt = j;
            }
        }
        
        
        r[smallest_bt].wt = t - r[smallest_bt].at;  // waiting time = current time - arrival time
        r[smallest_bt].rest = t - r[smallest_bt].at; // response time = waiting time (for SJF non preemptive)
        r[smallest_bt].rt = 0;
        t+=r[smallest_bt].bt;
        printf("%s\t|%d|\t", r[smallest_bt].pid, t);
        count ++;
        // Process execution and corresponding manipulation over
    }
    
    printf("\nCURRENT STATUS OF READY QUEUE\n");
    printf("PID\tAT\tBT\tWT\tREST\n");
    for(int i=0; i<n; i++) {
        avg_wt += r[i].wt;
        avg_tat+=(r[i].bt + r[i].wt);  // TAT = BT + WT
        avg_rest+=r[i].rest;
        printf("%s\t%d\t%d\t%d\t%d\n",r[i].pid,r[i].at,r[i].bt,r[i].wt,r[i].rest);

    }
    
    printf("AVERAGE WAITING TIME= %.2f\nAVERAGE TURNAROUND TIME = %.2f\nAVERAGE RESPONSE TIME = %.2f\nTHROUGHPUT=%.2f\n", (float)avg_wt/n, (float)avg_tat/n, (float)avg_rest/n, n/(float)(avg_tat-avg_wt));
    
    
    //SRTF 
    count = 0;
    t = 0;
    avg_wt = 0;
    avg_tat = 0;
    avg_rest = 0;
    smallest_bt = 0;
    for(int j=0; j<n; j++) {
        r[j].rt = r[j].bt;
    }
    
    printf("\n\nSRTF SCHEDULING\nGANTT CHART\n|0|\t");
    while(count < n) {
        for(int j=0; j<n; j++) {
            if((r[j].at <= t)&&(r[j].rt > 0)) {
                smallest_bt = j;
                break;
            }
        }
        
        for(int j=0; j<n; j++) {
            if((r[j].at <= t) && (r[j].rt < r[smallest_bt].bt)&&(r[j].rt>0)) {
                smallest_bt = j;
            }
        }
        
        // Manipulation start
        r[smallest_bt].rt = r[smallest_bt].rt - 1;
        if(r[smallest_bt].rt == (r[smallest_bt].bt - 1)) {
            r[smallest_bt].wt = t - r[smallest_bt].at;
        }
        t++;
        if(r[smallest_bt].rt == 0) {
            r[smallest_bt].wt = t- r[smallest_bt].at - r[smallest_bt].bt;
            count++;
        }
        printf("%s\t|%d|\t", r[smallest_bt].pid, t);
        // Manipulation end
    }
    
    printf("\nCURRENT STATUS OF READY QUEUE\n");
    printf("PID\tAT\tBT\tWT\tREST\n");
    for(int i=0; i<n; i++) {
        avg_wt += r[i].wt;
        avg_tat+=(r[i].bt+r[i].wt);
        avg_rest+=r[i].rest;
        printf("%s\t%d\t%d\t%d\t%d\n",r[i].pid,r[i].at,r[i].bt,r[i].wt,r[i].rest);
    }
    
     printf("AVERAGE WAITING TIME = %.2f\nAVERAGE TURNAROUND TIME = %.2f\nAVERAGE RESPONSE TIME = %.2f\nTHROUGHPUT = %.2f\n",(float)avg_wt/n,(float)avg_tat/n,(float)avg_rest/n,n/(float)(avg_tat-avg_wt));
    
}