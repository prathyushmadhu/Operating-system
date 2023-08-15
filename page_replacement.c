#include<stdio.h>

// Function to search
int search(int item, int len, int array[len]) {
    for(int i=0; i<len; i++) {
        if(array[i] == item) {
            return i;
        }
    }
    return -1;
}

// FIFO
void fifo(int len, int ref[len], int size) {
    int mem[size];
    int hit=0, miss=0;
    int first=0;
    int flag = -1;
    
    // size -> length of memory | len -> length of reference string
    
    for(int i=0; i<size; i++) {
        mem[i] = -1;
    }
    
    for(int i=0; i<len; i++) {
        flag = -1;
        
        // Condition for hit 
        if(search(ref[i],size,mem) != -1) {
            hit++;
        }
        else{
            miss++;
            
            // If empty space in memory
            for(int j=0; j<size; j++) {
                if(mem[j] == -1){
                    mem[j] = ref[i];
                    flag = 1;
                    break;
                }
            }
            
            // Memory occupied and need replacement
            if(flag == -1) {
                mem[first] = ref[i];
                first=(first+1)%size;
            }
        }
        
        for(int j=0; j<size; j++) {
            printf("%d\t",mem[j]);
        }
        printf("\n");
    }
    
    printf("Hit ratio: %d/%d\nMiss ratio: %d/%d\nPage faults: %d", hit, len, miss, len, miss);
}

// LRU
void lru(int len, int ref[len], int size) {
    int mem[size];
    int hit=0,miss=0;
    int flag=-1;
    int entry[size];
    int farthest=0;
    int count = 0;
    
    for(int i=0; i<size; i++) {
        mem[i] = -1;
    }
    
    for(int i=0; i<len; i++) {
        flag = -1;
        
        // Condition for hit
        if(search(ref[i], size, mem) != -1) {
            entry[search(ref[i], size, mem)] = i;
            hit++;
        }
        else {
            miss++;
            
            // If empty space in memory
            for(int j=0; j<size; j++) {
                if(mem[j] == -1) {
                    mem[j] = ref[i];
                    entry[j] = i;
                    flag = 1;
                    break;
                }
            }
            
            if(flag == -1) {
                farthest = 0;
                
                // To get least recently (farthest) added index 
                for(int j=0; j<size; j++) {
                    if(entry[j] < entry[farthest]) {
                        farthest = j;
                    }
                }
                
                mem[farthest] = ref[i];
                entry[farthest] = i;
                
            }
        }
        
        // Printing each state of memory buffer
        for(int j=0; j<size; j++) {
            printf("%d\t", mem[j]);
        }
        printf("\n");
    }
    printf("Hit ratio: %d/%d\nMiss ratio: %d/%d\nPage faults: %d", hit, len, miss, len, miss);
}

// Optimal
void optimal(int len, int ref[len], int size) {
    
}