#include <iostream>
using namespace std;

struct Process {
    int ccode;       // course code
    int duration;    // class duration
    int priority;    // priority (ignored in FCFS)
    int arrival_time; // preferred arrival time (ignored in FCFS)
};

// Fungsi untuk kira waktu menunggu (waiting time)
void findWaitingTimeFCFS(Process proc[], int n, int wt[]) {
    wt[0] = 0; // proses pertama tak tunggu
    for (int i = 1; i < n; i++) {
        wt[i] = proc[i - 1].duration + wt[i - 1];
    }
}

// Fungsi untuk kira turnaround time
void findTurnAroundTimeFCFS(Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].duration + wt[i];
    }
}

// Fungsi untuk papar hasil FCFS
void printFCFSResults(Process proc[], int n, int wt[], int tat[]) {
    float total_wt = 0, total_tat = 0;
    cout << "FCFS Scheduling Order:\n";
    for (int i = 0; i < n; i++) {
        cout << "Course " << proc[i].ccode << " ";
        total_wt += wt[i];
        total_tat += tat[i];
    }
    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
}

int main() {
    // Input kursus: {course code, duration, priority, arrival time}
    Process proc[] = {{2201, 3, 2, 1}, {3401, 2, 3, 2}, {1103, 1, 1, 3}};
    int n = sizeof(proc) / sizeof(proc[0]);

    int wt[n], tat[n];

    // Langkah-langkah FCFS
    findWaitingTimeFCFS(proc, n, wt);
    findTurnAroundTimeFCFS(proc, n, wt, tat);
    printFCFSResults(proc, n, wt, tat);

    return 0;
}
