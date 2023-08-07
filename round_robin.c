#include<stdio.h>
struct RQ {
    char pname[3];
    int at, rt, inside, tt, bt;
};

int main() {
    int rq[10], nq[20];
    struct RQ r[10];
    int queue[50], front=0, rear=-1;
    printf("ENTER NUMBER OF PROCESS : ");
    int n;
    scanf(" %d",&n);
    int ts;
    int sum_bt=0;
    
    for(int i=0; i<n; i++) {
        printf("ENTER PROCESS NAME : ");
        scanf(" %s",r[i].pname);
        printf("ENTER PROCESS ARRIVAL TIME : ");
        scanf(" %d",&r[i].at);
        printf("ENTER PROCESS BURST TIME : ");
        scanf(" %d",&r[i].bt);
        r[i].rt=r[i].bt;
        r[i].inside = 0;  // 0-> not inside ready queue | 1-> inside ready queue
        r[i].tt = 0;
        sum_bt += r[i].rt;
    }
    
    int t = 0;
    int count = 0;
    int p,add=0;
    
    // Sort based on ARRIVAL
    for (int i=0;i<n;i++) {
        for (int j=0;j<n-1;j++) {
            if ( r[j].at > r[j+1].at ) {
                struct RQ temp = r[j];
                r[j]=r[j+1];
                r[j+1]=temp;
                
            }
        }
    }
    
    int ch;
    
    // Menu driven for time slice in RR
    do {
        printf("MENU \n1) 2ms\n2) 4ms\n3) 5ms\n4) 8ms\n5) 10ms\n6)EXIT\nENTER CHOICE : ");
        scanf(" %d",&ch);
        count=0;
        
        switch(ch) {
            case 1 :
                ts=2;
                break;
            case 2 :
                ts=4;
                break;
            case 3 :
                ts=5;
                break;
            case 4 :
                ts=8;
                break;
            case 5 :
                ts=10;
                break;
            case 6 :
                count = n;
                break;
            default :
                printf("ENTER INVALID CHOICE! \n");
                count = n;
        }
        
        t = 0;
        add=0;
        front=0;
        rear=-1;

        if (count==0) {
            printf("0 | \t");
            for (int i=0 ; i<n ; i++) {
                r[i].rt=r[i].bt;
                r[i].inside = 0;
                r[i].tt = 0;
            }
        }
        
        while (count!=n) {
            //choosing process to queue
            for (int i=0;i<n;i++) {
                if((r[i].at<=t) && (r[i].inside == 0)) {
                    r[i].inside = 1;
                    queue[++rear] = i;
                }
            }
            
            //adding pending process to queue
            if (add==1) {
                queue[++rear] = p;
            }
            
            //choose p
            p = queue[front++];

            //doing process
            if (r[p].rt <= ts) {  // ts -> time slice
                add=0;
                t += r[p].rt;
                r[p].tt = t-r[p].at;
                r[p].rt = 0;
            }
            
            if (r[p].rt > ts ) {
                add=1;
                r[p].rt -= ts;
                t += ts;
            }
            printf("%s\t|%d|\t",r[p].pname,t);
            
            //check if all complete
            count=0;
            for (int i=0 ; i<n ; i++) {
                if (r[i].rt==0) {
                    count++;
                }
            }
        }
        
        if((ch>0)&&(ch<6)) {
            //find time
            float avg_tat = 0;
            for (int i=0 ; i<n ; i++) {
                avg_tat += r[i].tt;
            }
            
            printf("\nAVERAGE TURN AROUND TIME : %f",avg_tat/n);
            avg_tat -= sum_bt;
            printf("\nAVERAGE WAITING TIME : %f",avg_tat/n);
            printf("\nTHROUGHPUT : %f\n",(float)n/t);
        }
        
    }while(ch!=6);
    
 return 0;
}
