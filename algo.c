#include <stdio.h>
#include <stdlib.h>

struct Process {
    char name;
    int arrival_time, burst_time, waiting_time, turnaround_time;
} *processes;

void FCFS(int n) {
    processes[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
    }
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
        printf("Process %c - Waiting Time: %d - Turnaround Time: %d\n", processes[i].name, processes[i].waiting_time, processes[i].turnaround_time);
    }
    int avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time = avg_waiting_time / n;
    avg_turnaround_time = avg_turnaround_time / n;
    printf("Average Waiting Time: %d\n", avg_waiting_time);
    printf("Average Turnaround Time: %d\n", avg_turnaround_time);
}

void SJF(int n) {
    // Sort processes based on burst time (Shortest Job First)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    // Calculate waiting and turnaround times for SJF
    processes[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
    }
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
        printf("Process %c - Waiting Time: %d - Turnaround Time: %d\n", processes[i].name, processes[i].waiting_time, processes[i].turnaround_time);
    }
    int avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time = avg_waiting_time / n;
    avg_turnaround_time = avg_turnaround_time / n;
    printf("Average Waiting Time: %d\n", avg_waiting_time);
    printf("Average Turnaround Time: %d\n", avg_turnaround_time);
}

int main() {
    int algorithm;
    printf("Choose the algorithm to implement (1 for FCFS, 2 for SJF): ");
    scanf("%d", &algorithm);
    int n;

    switch (algorithm) {
        case 1:
            printf("Enter number of processes: ");
            scanf("%d", &n);

            processes = (struct Process*) malloc(n * sizeof(struct Process));
            for (int i = 0; i < n; i++) {
                printf("Enter details for process %d\n", i + 1);
                printf("Enter name: ");
                scanf(" %c", &processes[i].name);
                printf("Enter arrival time: ");
                scanf("%d", &processes[i].arrival_time);
                printf("Enter burst time: ");
                scanf("%d", &processes[i].burst_time);
            }
            FCFS(n);
            break;
        case 2:
            printf("Enter number of processes: ");
            scanf("%d", &n);

            processes = (struct Process*) malloc(n * sizeof(struct Process));
            for (int i = 0; i < n; i++) {
                printf("Enter details for process %d\n", i + 1);
                printf("Enter name: ");
                scanf(" %c", &processes[i].name);
                printf("Enter arrival time: ");
                scanf("%d", &processes[i].arrival_time);
                printf("Enter burst time: ");
                scanf("%d", &processes[i].burst_time);
            }
            SJF(n);
            break;
        default:
            printf("Invalid choice. Exiting...\n");
            exit(1);
    }


    free(processes);
    return 0;
}
