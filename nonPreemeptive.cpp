#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    char name;
    int arrival_time, burst_time, waiting_time, turnaround_time;
};

void FCFS(vector<Process>& processes) {
    processes[0].waiting_time = 0;
    for (int i = 1; i < processes.size(); i++) {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
    }
    for (int i = 0; i < processes.size(); i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

void SJF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.burst_time < b.burst_time;
    });

    processes[0].waiting_time = 0;
    for (int i = 1; i < processes.size(); i++) {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
    }
    for (int i = 0; i < processes.size(); i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

int main() {
    int n, algorithm;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter details for process " << i + 1 << endl;
        cout << "Enter name: ";
        cin >> processes[i].name;
        cout << "Enter arrival time: ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time: ";
        cin >> processes[i].burst_time;
    }

    cout << "Choose algorithm (1 for FCFS, 2 for SJF): ";
    cin >> algorithm;

    if (algorithm == 1) {
        FCFS(processes);
    } else if (algorithm == 2) {
        SJF(processes);
    } else {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    int avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
        cout << "Process " << processes[i].name << " - Waiting Time: " << processes[i].waiting_time
             << " - Turnaround Time: " << processes[i].turnaround_time << endl;
    }

    avg_waiting_time = avg_waiting_time / n;
    avg_turnaround_time = avg_turnaround_time / n;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;

    return 0;
}
