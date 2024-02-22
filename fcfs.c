#include <stdio.h> 
#include <stdlib.h>

//first, we create the structure of the process
struct Process { 
    char name;
    int arrival_time, burst_time, waiting_time, turnaround_time;
}*processes;

void sortProcesses(int n) {
    // Sort processes according to arrival time in ascending order using bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
//FCFS function to calculate waiting time and turn around time
void FCFS(int n) {
    //sorting processes
    sortProcesses(n);
    //first process will always have 0 waiting time in FCFS
    processes[0].waiting_time = 0;
    int completion_time = 0;
    //calculating turnaround time
    for(int i = 0; i < n; i++) {
        if(processes[i].arrival_time > completion_time)
            completion_time += processes[i].arrival_time - completion_time;
        completion_time += processes[i].burst_time;
        processes[i].turnaround_time = completion_time - processes[i].arrival_time;
    }
    //to calculate waiting time
    for(int i = 0; i < n; i++) {
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
    int avg_waiting_time = 0, avg_turnaround_time = 0; 
    for(int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time; 
        avg_turnaround_time += processes[i].turnaround_time; 
        printf("Process %c - Waiting Time: %d - Turnaround Time: %d\n", processes[i].name, processes[i].waiting_time, 
        processes[i].turnaround_time);
    }
    avg_waiting_time = avg_waiting_time/n;
    avg_turnaround_time = avg_turnaround_time/n; 
    printf("Average Waiting Time: %d\n", avg_waiting_time);
    printf("Average Turnaround Time: %d\n", avg_turnaround_time);
}

//main function to create processes dynamically and take input
int main() {
    int n;
    printf("Enter number of processes: "); 
    scanf("%d", &n);
    //dynamically allocating memory on the basis of number of processes 
    processes = (struct Process*) malloc(n * sizeof(struct Process)); 
    for(int i = 0; i < n; i++) {
        printf("Enter details for process %d\n", i+1); 
        printf("Enter name: ");
        scanf(" %c", &processes[i].name); 
        printf("Enter arrival time: "); 
        scanf("%d", &processes[i].arrival_time); 
        printf("Enter burst time: "); 
        scanf("%d", &processes[i].burst_time);
    }
    FCFS(n);
    //Adding another process 
    n++;
    printf("Enter details for the additional process\n"); 
    processes = (struct Process*) realloc(processes, n * sizeof(struct Process)); 
    printf("Enter name: ");
    scanf(" %c", &processes[n-1].name); 
    printf("Enter arrival time: "); 
    scanf("%d", &processes[n-1].arrival_time); 
    printf("Enter burst time: ");
    scanf("%d", &processes[n-1].burst_time); 
    FCFS(n);
    free(processes); 
    return 0;
}
