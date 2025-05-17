#include <iostream>
using namespace std;

struct Process {
    int ccode;       // course code
    int duration;    // class duration
    int priority;    // priority
    int arrival_time; // preferred arrival time
};

// function to calculate waiting time
void findWaitingTime(Process proc[], int n, int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = proc[i - 1].duration + wt[i - 1];
    }
}

// funtion to calculate turnaround time
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].duration + wt[i];
    }
}

// function to print results
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

// FCFS scheduling
void fcfsScheduling(Process proc[], int n) {
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

int main() {
    // Input: {course code, duration, priority, arrival time}
    Process proc[] = {
        {2201, 3, 2, 1},
        {3401, 2, 3, 2},
        {1103, 1, 1, 3}
    };
    int n = sizeof(proc) / sizeof(proc[0]);

    // original data
    Process proc_fcfs[3];
    for (int i = 0; i < n; i++) {
        proc_fcfs[i] = proc[i];
    }

    // FCFS
    fcfsScheduling(proc_fcfs, n);

    return 0;
}
