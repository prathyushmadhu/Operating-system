#include<stdio.h>
int main() {
    int c;
    int n;
    int memory[50];
    int p;
    int process[50];
    int alloc[50];
    int sum=0;
    
    do {
        printf("\n\nMENU\n1.INITIALISATION\n2.FIRST FIT\n3.BEST FIT\n4.WORST FIT\n5.EXIT\nENTER YOUR CHOICE: ");
        
        scanf("%d",&c);
        switch(c) {
            case 1:
                printf("\n\nEnter number of blocks: ");
                scanf("%d",&n);
                
                for(int i=0; i<n; i++) {
                    printf("Enter size of the block M%d: ",i);
                    scanf("%d",&memory[i]);
                }
                
                printf("Enter number of process");
                scanf("%d",&p);
                
                for(int i=0; i<p; i++) {
                    printf("Enter size of the process P%d: ",i);
                    scanf("%d",&process[i]);
                }
                break;
                
            case 2:
                sum=0;
                
                // ALLOCATION for each block
                for(int i=0; i<n; i++) {
                    alloc[i] = 0;
                }
                printf("\n\n....Implementing first fit allocation....\n");
                for(int i=0; i<p; i++) {
                    printf("P%d\t",i);
                }
                printf("\n");
                
                // FIRST FIT
                for(int i=0; i<p; i++) {
                    int flag=0;
                    for(int j=0; j<n; j++) {
                        if((memory[j] >= process[i]) && (alloc[j]==0)) {
                            alloc[j] = 1;
                            sum += (memory[j] - process[i]);
                            printf("M%d\t",j);
                            flag = 1;
                            break;
                        }
                    }
                    
                    if(!flag) {
                        printf("\nCannot allocate all processes");
                        break;
                    }
                }
                
                printf("\ntotal Memory wastage due to internal fragmentation = %d\n",sum);
                break;
                
            case 3:
                sum = 0;
                
                // ALLOCATION for each block
                for(int i=0; i<n; i++) {
                     alloc[i] = 0;
                }
                
                printf("\n\n...Implementing best fit allocation....\n");
                for(int i=0; i<p; i++) {
                    printf("P%d\t",i);
                }
                printf("\n");
                
                // BEST FIT
                for(int i=0; i<p; i++) {
                    int flag=0;
                    int smallest_value = 65535, smallest;
                    for(int j=0; j<n; j++) {
                        if((memory[j] >= process[i]) && (memory[j] < smallest_value) && (alloc[j] == 0)) {
                            smallest = j;
                            smallest_value = memory[j];
                            flag = 1;
                        }
                    }
                    
                    if(!flag) {
                        printf("\nCannot allocate all processes");
                        break;
                    }
                    else {
                        alloc[smallest] = 1;
                        sum += (memory[smallest] - process[i]);
                        printf("M%d\t",smallest);
                    }
                }
                
                printf("\ntotal Memory wastage due to internal fragmentation = %d\n",sum);
                break;
                
            case 4:
                sum = 0;
                for(int i=0; i<n; i++) {
                    alloc[i] = 0;
                }
                    
                printf("\n\n...Implementing worst fit allocation....\n");
                for(int i=0; i<p; i++) {
                    printf("P%d\t",i);
                }
                printf("\n");
                
                // WORST FIT
                for(int i=0; i<p; i++) {
                    int flag=0;
                    int largest_value = 0, largest;
                    for(int j=0; j<n; j++) {
                        if((memory[j] >= process[i]) && (memory[j] > largest_value) && (alloc[j] == 0)) {
                            largest = j;
                            largest_value = memory[largest];
                            flag = 1;
                        }
                    }
                    
                    if(!flag) {
                        printf("\nCannot allocate all process.");
                        break;
                    }
                    else {
                        alloc[largest] = 1;
                        sum += (memory[largest] - process[i]);
                        printf("M%d\t",largest);
                    }
                }
                
                printf("\ntotal Memory wastage due to internal fragmentation = %d\n",sum);
                break;
                
            case 5:
                printf("EXITING...\n");
                break;
            default:
                printf("\nEnter valid choice\n");
        }
    }while(c!=5);
}