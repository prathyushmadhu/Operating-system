#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void fcfs_scheduling(int num_processes, int burst_times[], int sum);
void sjf_scheduling(int num_processes, int burst_times[], int sum);

// FCFS Schedulig algorithm
void fcfs_scheduling(int num_processes, int burst_time[], int sum) {
    int i, waiting_time[num_processes], turnaround_time[num_processes];
    float average_waiting_time = 0, average_turnaround_time = 0;

    waiting_time[0] = 0;
    turnaround_time[0] = burst_time[0];
    
     for(i=1; i<num_processes; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }

    // FCFS Scheduling Gantt Chart
    printf("\nFCFS Scheduling Gantt Chart:\n");
    printf(" ");
    for (i = 0; i < num_processes; i++) {
        printf("|  P%d  ", i + 1);
    }
    printf("|\n");

    printf("0");
    for (i = 0; i < num_processes; i++) {
        printf("     %d", turnaround_time[i]);
    }
    printf("\n");

    printf("\nFCFS Scheduling:\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0; i<num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i+1, burst_time[i], waiting_time[i], turnaround_time[i]);
        average_waiting_time += waiting_time[i];
        average_turnaround_time += turnaround_time[i];
    }

    average_waiting_time /= num_processes;
    average_turnaround_time /= num_processes;
    float throughput = num_processes / (float)sum;

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Throughput: %.2f processes per time unit\n", throughput);
}

// SJF Scheduling algorithm
void sjf_scheduling(int num_processes, int burst_time[], int sum) {
    int i, j, min_index, temp;
    int waiting_time[num_processes], turnaround_time[num_processes];
    float average_waiting_time = 0, average_turnaround_time = 0;

    // Sorting algorithm
    for(i=0; i<num_processes; i++) {
        min_index = i;
        for(j=i+1; j<num_processes; j++){
            if(burst_time[j] < burst_time[min_index])
                min_index = j;
        }

        temp = burst_time[i];
        burst_time[i] = burst_time[min_index];
        burst_time[min_index] = temp;
    }

    waiting_time[0] = 0;
    turnaround_time[0] = burst_time[0];
    
    for(i=1; i<num_processes; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }

    // SJF Scheduling Gantt Chart:
    printf("\nSJF Scheduling Gantt Chart:\n");
    printf(" ");
    for (i = 0; i < num_processes; i++) {
        printf("|  P%d  ", i + 1);
    }
    printf("|\n");

    printf("0");
    for (i = 0; i < num_processes; i++) {
        printf("     %d", turnaround_time[i]);
    }
    printf("\n");

    for(i=1; i<num_processes; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }

    printf("\nSJF Scheduling:\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0; i<num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i+1, burst_time[i], waiting_time[i], turnaround_time[i]);
        average_waiting_time += waiting_time[i];
        average_turnaround_time += turnaround_time[i];
    }

    average_waiting_time /= num_processes;
    average_turnaround_time /= num_processes;
    float throughput = num_processes / (float)sum;

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Throughput: %.2f processes per time unit\n", throughput);
}

int main() {
    int num_processes, i, choice, sum=0;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    int burst_time[num_processes];

    printf("Enter the burst times for ech process:\n");
    for(i=0; i<num_processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        sum += burst_time[i];
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. FCFS Scheduling\n");
        printf("2. SJF Scheduling\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs_scheduling(num_processes, burst_time, sum);
                break;
            case 2:
                sjf_scheduling(num_processes, burst_time, sum);
                break;
            case 3:
                printf("Existing the program. \n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");

        }


    }
}
