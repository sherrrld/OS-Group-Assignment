#include <iostream>
#include <climits>
using namespace std;

struct Process {
    int ccode;         // course code
    int duration;      // class duration
    int priority;      // priority
    int arrival_time;  // preferred arrival time
};

// Function to calculate waiting time for ordered process list
void calculateWaitingTime(Process proc[], int n, int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + proc[i - 1].duration;
    }
}

// Function to calculate turnaround time from waiting time
void calculateTurnaroundTime(Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].duration + wt[i];
    }
}

// Function to print results
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

// FCFS Scheduling (ignores arrival time and priority)
void fcfsScheduling(Process proc[], int n) {
    int wt[n], tat[n];
    calculateWaitingTime(proc, n, wt);
    calculateTurnaroundTime(proc, n, wt, tat);
    printResults("FCFS", proc, n, wt, tat);
}

// Non-preemptive Priority Scheduling (uses arrival time and priority)
void priorityScheduling(Process proc[], int n) {
    bool completed[n] = {false};
    int currentTime = 0;
    int wt[n], tat[n];
    Process scheduled[n];
    int count = 0;

    while (count < n) {
        int idx = -1;
        int minPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && proc[i].arrival_time <= currentTime) {
                if (proc[i].priority < minPriority) {
                    minPriority = proc[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            wt[count] = currentTime - proc[idx].arrival_time;
            if (wt[count] < 0) wt[count] = 0;
            currentTime += proc[idx].duration;
            tat[count] = wt[count] + proc[idx].duration;
            scheduled[count] = proc[idx];
            completed[idx] = true;
            count++;
        } else {
            currentTime++;
        }
    }

    printResults("Priority Scheduling", scheduled, n, wt, tat);
}

int main() {
    // Input: {course code, duration, priority, arrival time}
    Process proc[] = {
        {2201, 3, 2, 1},
        {3401, 2, 3, 2},
        {1103, 1, 1, 3}
    };
    int n = sizeof(proc) / sizeof(proc[0]);

    // Make copies for both scheduling methods
    Process proc_fcfs[3], proc_priority[3];
    for (int i = 0; i < n; i++) {
        proc_fcfs[i] = proc[i];
        proc_priority[i] = proc[i];
    }

    // Run FCFS (no arrival time used)
    fcfsScheduling(proc_fcfs, n);

    // Run Priority Scheduling (uses arrival time)
    priorityScheduling(proc_priority, n);

    return 0;
}
