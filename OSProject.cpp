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
        for (int j = i + 1; j
