#include<stdio.h>
int N, M;

int Safety(int ALLOCATION[N][M], int AVAILABLE[M], int NEED[N][M]) {
    int work[M];
    
    // Copying AVAILABLE to WORK
    for(int i=0; i<M; i++) {
        work[i] = AVAILABLE[i];
    }
    
    // FINISH to mark finished process
    int finish[N];
    for(int i=0; i<N; i++) {
        finish[i] = 0;
    }
    
    int pro_inc = N;
    int r_sat, p_comp = 0;
    
    // do loop
    do {
        p_comp = 0;  // No of process completed
        for(int i=0; i<N; i++) {
            r_sat = 0;  // Resource that satisfy `need <= work` 
            
            // If process is not completed
            if(finish[i] == 0) {
                for(int j=0; j<M; j++) {
                    if(NEED[i][j] <= work[j]) {
                        r_sat++;
                    }
                    else {
                        break;
                    }
                }
                
                // If number of resource satisfy == total no of resource
                // this => process is complete
                if(r_sat == M) {
                    finish[i] = 1;
                    pro_inc--;
                    
                    // process complete => work = work + ALLOCATION
                    for(int j=0; j<M; j++) {
                        work[j] += ALLOCATION[i][j];
                    }
                     // Print the process completed | Sequence print
                     printf("P%d\t",i);
                     p_comp = 1;
                    
                }
            }
        }
        
        // If the process is completed (outside process loop)
        if(p_comp == 0) {
            
            // process not complete and all process not in sequence | UNSAFE
            if(pro_inc != 0) {
                return 0;
            }
            return 1;
        }
    }while(1);
}


// MAIN PROGRAM
int main() {
    printf("Enter number of process: ");
    scanf("%d",&N);
    printf("Enter number of resources: ");
    scanf("%d",&M);
    
    int MAX[N][M];
    int AVAILABLE[M];
    int ALLOCATION[N][M];
    int NEED[N][M];
    int INSTANCE[M];
    
    // Taking INSTANCE of each resource | Available = 0
    for(int i=0; i<M; i++) {
        printf("Enter number of instance of R%d: ", i);
        scanf("%d",&INSTANCE[i]);
        AVAILABLE[i]=0;
    }
    
    // Taking values of MAX needed for the process
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            printf("Enter how much instance of R%d is required for P%d: ",j,i);
            scanf("%d",&MAX[i][j]);
        }
    }
    
    // Taking values of ALLOCATION (allocated instances)
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            printf("Enter how much instance of R%d is allocated for P%d: ",j,i);
            scanf("%d",&ALLOCATION[i][j]);
        }
    }
    
    printf("\nMAX MATRIX\n");
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            printf("%d\t",MAX[i][j]);
        }
        printf("\n");
    }
    
    printf("\nNEED MATRIX\n");
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
            printf("%d\t",NEED[i][j]);
        }
        printf("\n");
    }
    
    printf("\nALLOCATION MATRIX\n");
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            printf("%d\t",ALLOCATION[i][j]);
        }
        printf("\n");
    }
    
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            AVAILABLE[j] += ALLOCATION[i][j];
        }
    }
    printf("\nAVAILABLE VECTOR\n");
    for(int i=0; i<M; i++) {
        AVAILABLE[i] = INSTANCE[i] - AVAILABLE[i];
        printf("%d\t",AVAILABLE[i]);
    }
    printf("\n\n");
    
    // Checking wheather sequence is safe or not 
    if(!(Safety(ALLOCATION, AVAILABLE, NEED))) {
        printf("\nNO SAFE SEQUENCE....DEADLOCK\n");
    }
    else{
        printf("\nSAFE SEQUENCE IS ABOVE\n");
    }
    
    // When a process request for resource instance
    int REQUEST[M];
    int pid;
    printf("\n\nENTER PROCESS ID TO CHANGE: ");
    scanf("%d",&pid);
    
    for(int i=0; i<M; i++) {
        printf("Enter how much more of R%d is required: ",i);
        scanf("%d",&REQUEST[i]);
        AVAILABLE[i] -= REQUEST[i];
        ALLOCATION[pid][i] += REQUEST[i];
        NEED[pid][i] -= REQUEST[i];
    }
    
    printf("\n\n");
    
    if(!(Safety(ALLOCATION, AVAILABLE, NEED))) {
        printf("\nNO SAFE SEQUENCE....DEADLOCK\n");
    }
    else{
        printf("\nREQUEST GRANTED....SAFE SEQUENCE IS ABOVE\n");
    }
    
}