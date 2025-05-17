#include <iostream>
#include <climits>
using namespace std;

struct Process {
    int ccode;         // course code
    int duration;      // class duration
    int priority;      // priority (lower is higher)
    int arrival_time;  // preferred arrival time
};

// Calculate waiting time
void findWaitingTime(Process proc[], int n, int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = proc[i - 1].duration + wt[i - 1];
    }
}

// Calculate turnaround time
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].duration + wt[i];
    }
}

// Print scheduling results
void printResults(string algoName, Process proc[], int n, int wt[], int tat[]) {
    float total_wt = 0, total_tat = 0;
    cout << "\n" << algoName << " Scheduling Order:\n";
    for (int i = 0; i < n; i++) {
        cout << "Course " << proc[i].ccode << " ";
        total_wt += wt[i];
        total_tat += tat[i];
    }
    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
}

// FCFS scheduling using arrival time
void fcfsScheduling(Process proc[], int n) {
    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[j].arrival_time < proc[i].arrival_time) {
                swap(proc[i], proc[j]);
            }
        }
    }

    int wt[n], tat[n];
    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);
    printResults("FCFS", proc, n, wt, tat);
}

// Non-preemptive priority scheduling using arrival time
void priorityScheduling(Process proc[], int n) {
    bool done[n] = {false};
    int currentTime = 0;
    int completed = 0;
    int wt[n], tat[n];
    Process result[n];

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Find the highest priority among arrived processes
        for (int i = 0; i < n; i++) {
            if (!done[i] && proc[i].arrival_time <= currentTime) {
                if (proc[i].priority < highestPriority) {
                    highestPriority = proc[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime++; // No class ready yet
            continue;
        }

        wt[idx] = currentTime - proc[idx].arrival_time;
        if (wt[idx] < 0) wt[idx] = 0;

        currentTime += proc[idx].duration;
        tat[idx] = wt[idx] + proc[idx].duration;
        result[completed++] = proc[idx];
        done[idx] = true;
    }

    printResults("Priority (w/ Arrival Time)", result, n, wt, tat);
}

int main() {
    // Input: {course code, duration, priority, arrival time}
    Process proc[] = {
        {2201, 3, 2, 1},
        {3401, 2, 3, 2},
        {1103, 1, 1, 3}
    };
    int n = sizeof(proc) / sizeof(proc[0]);

    // Clone original process list for both algorithms
    Process proc_fcfs[3], proc_priority[3];
    for (int i = 0; i < n; i++) {
        proc_fcfs[i] = proc[i];
        proc_priority[i] = proc[i];
    }

    // Run both scheduling algorithms
    fcfsScheduling(proc_fcfs, n);
    priorityScheduling(proc_priority, n);

    return 0;
}
