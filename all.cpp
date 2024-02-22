#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Process structure to store process details
struct Process {
    char name;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Function to calculate waiting time and turnaround time for FCFS algorithm
void FCFS(vector<Process>& processes) {
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    // Calculate waiting time and turnaround time
    int total_waiting_time = 0, total_turnaround_time = 0;
    cout << "FCFS Gantt Chart:" << endl;
    for (int i = 0; i < processes.size(); ++i) {
        if (i == 0 || processes[i].arrival_time > processes[i - 1].turnaround_time) {
            processes[i].waiting_time = 0;
        } else {
            processes[i].waiting_time = processes[i - 1].turnaround_time - processes[i].arrival_time;
        }
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        // Display Gantt chart
        cout << "| " << processes[i].name << " ";
    }
    cout << "|" << endl;

    // Calculate average waiting time and turnaround time
    double avg_waiting_time = static_cast<double>(total_waiting_time) / processes.size();
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / processes.size();

    // Display results
    cout << "FCFS Results:" << endl;
    for (int i = 0; i < processes.size(); ++i) {
        cout << "Process " << processes[i].name << " - Waiting Time: " << processes[i].waiting_time << " - Turnaround Time: " << processes[i].turnaround_time << endl;
    }
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << endl;
}

// Function to calculate waiting time and turnaround time for SJF algorithm
void SJF(vector<Process>& processes) {
    // Sort processes based on burst time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.burst_time < b.burst_time;
    });

    // Calculate waiting time and turnaround time
    int total_waiting_time = 0, total_turnaround_time = 0;
    cout << endl << "SJF Gantt Chart:" << endl;
    for (int i = 0; i < processes.size(); ++i) {
        if (i == 0 || processes[i].arrival_time > processes[i - 1].turnaround_time) {
            processes[i].waiting_time = 0;
        } else {
            processes[i].waiting_time = processes[i - 1].turnaround_time - processes[i].arrival_time;
        }
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        // Display Gantt chart
        cout << "| " << processes[i].name << " ";
    }
    cout << "|" << endl;

    // Calculate average waiting time and turnaround time
    double avg_waiting_time = static_cast<double>(total_waiting_time) / processes.size();
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / processes.size();

    // Display results
    cout << "SJF Results:" << endl;
    for (int i = 0; i < processes.size(); ++i) {
        cout << "Process " << processes[i].name << " - Waiting Time: " << processes[i].waiting_time << " - Turnaround Time: " << processes[i].turnaround_time << endl;
    }
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << endl;
}

// Function to calculate waiting time and turnaround time for SRJF algorithm
void SRJF(vector<Process>& processes) {
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    // Priority queue to store processes based on remaining burst time
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int current_time = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;
    cout << endl << "SRJF Gantt Chart:" << endl;

    while (!pq.empty() || !processes.empty()) {
        // Push processes that have arrived
        while (!processes.empty() && processes.front().arrival_time <= current_time) {
            pq.push({processes.front().burst_time, processes.front().name});
            processes.erase(processes.begin());
        }

        if (!pq.empty()) {
            // Get process with shortest remaining burst time
            auto [burst_time, name] = pq.top();
            pq.pop();

            // Calculate waiting time and turnaround time
            int waiting_time = current_time;
            int turnaround_time = waiting_time + burst_time;

            // Update current time and total times
            current_time += burst_time;
            total_waiting_time += waiting_time;
            total_turnaround_time += turnaround_time;

            // Display Gantt chart
            cout << "| " << name << " ";

            // Update waiting time and turnaround time for the process
            for (auto& process : processes) {
                if (process.name == name) {
                    process.waiting_time = waiting_time;
                    process.turnaround_time = turnaround_time;
                    break;
                }
            }

            // Update remaining burst times for other processes
            for (auto& process : processes) {
                if (process.arrival_time <= current_time) {
                    pq.push({process.burst_time, process.name});
                }
            }
        } else {
            current_time = processes.front().arrival_time;
        }
    }
    cout << "|" << endl;

    // Calculate average waiting time and turnaround time
    double avg_waiting_time = static_cast<double>(total_waiting_time) / processes.size();
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / processes.size();

    // Display results
    cout << "SRJF Results:" << endl;
    for (const auto& process : processes) {
        cout << "Process " << process.name << " - Waiting Time: " << process.waiting_time << " - Turnaround Time: " << process.turnaround_time << endl;
    }
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << endl;
}

// Function to simulate Round Robin scheduling algorithm
void RoundRobin(vector<Process>& processes, int quantum) {
    queue<Process> q;
    int current_time = 0, total_waiting_time = 0, total_turnaround_time = 0;
    cout << endl << "Round Robin Gantt Chart (Quantum = " << quantum << "):" << endl;

    int remaining_burst_time[processes.size()];
    for (int i = 0; i < processes.size(); ++i) {
        remaining_burst_time[i] = processes[i].burst_time;
    }

    int idx = 0;
    q.push(processes[idx]);
    ++idx;

    while (!q.empty()) {
        Process current_process = q.front();
        q.pop();

        // Execute current process for the quantum or remaining burst time, whichever is smaller
        int execute_time = min(quantum, remaining_burst_time[current_process.name - 'A']);
        current_time += execute_time;

        // Update remaining burst time
        remaining_burst_time[current_process.name - 'A'] -= execute_time;

        // Display Gantt chart
        cout << "| " << current_process.name << " ";

        // Push back processes that have arrived and are not yet executed
        for (; idx < processes.size(); ++idx) {
            if (processes[idx].arrival_time <= current_time) {
                q.push(processes[idx]);
            } else {
                break;
            }
        }

        // Push back current process if it has remaining burst time
        if (remaining_burst_time[current_process.name - 'A'] > 0) {
            q.push(current_process);
        } else {
            // Calculate waiting time and turnaround time
            int waiting_time = current_time - current_process.burst_time - current_process.arrival_time;
            int turnaround_time = waiting_time + current_process.burst_time;

            // Update total times
            total_waiting_time += waiting_time;
            total_turnaround_time += turnaround_time;

            // Update waiting time and turnaround time for the process
            for (auto& process : processes) {
                if (process.name == current_process.name) {
                    process.waiting_time = waiting_time;
                    process.turnaround_time = turnaround_time;
                    break;
                }
            }
        }
    }
    cout << "|" << endl;

    // Calculate average waiting time and turnaround time
    double avg_waiting_time = static_cast<double>(total_waiting_time) / processes.size();
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / processes.size();

    // Display results
    cout << "Round Robin Results:" << endl;
    for (const auto& process : processes) {
        cout << "Process " << process.name << " - Waiting Time: " << process.waiting_time << " - Turnaround Time: " << process.turnaround_time << endl;
    }
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << endl;
}

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        cout << "Enter details for process " << i + 1 << endl;
        cout << "Enter name: ";
        cin >> processes[i].name;
        cout << "Enter arrival time: ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time: ";
        cin >> processes[i].burst_time;
    }

    FCFS(processes);
    SJF(processes);
    SRJF(processes);

    cout << "Enter time quantum for Round Robin: ";
    cin >> quantum;
    RoundRobin(processes, quantum);

    return 0;
}
