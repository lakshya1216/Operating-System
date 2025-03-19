#include <stdio.h>
#define MAX 10

int pid[MAX], arrival_time[MAX], burst_time[MAX], queue[MAX], remaining_time[MAX], completion_time[MAX];

void round_robin(int n, int quantum) {
    int time = 0, i, done;

    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (queue[i] == 1 && remaining_time[i] > 0) {  // Queue 1 - Round Robin
                done = 0;
                if (time < arrival_time[i]) {
                    time = arrival_time[i];
                }

                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    remaining_time[i] = 0;
                    completion_time[i] = time;
                }
            }
        }
    } while (!done);
}

void fcfs(int n) {
    int time = 0, i;

    for (i = 0; i < n; i++) {
        if (queue[i] == 2 && remaining_time[i] > 0) {  // Queue 2 - FCFS
            if (time < arrival_time[i]) {
                time = arrival_time[i];
            }
            time += remaining_time[i];
            remaining_time[i] = 0;
            completion_time[i] = time;
        }
    }
}

float calculate_avg_tat(int n) {
    int total_tat = 0;
    for (int i = 0; i < n; i++) {
        int tat = completion_time[i] - arrival_time[i];
        total_tat += tat;
    }
    return (float) total_tat / n;
}

float calculate_avg_wt(int n) {
    int total_wt = 0;
    for (int i = 0; i < n; i++) {
        int tat = completion_time[i] - arrival_time[i];
        int wt = tat - burst_time[i];
        total_wt += wt;
    }
    return (float) total_wt / n;
}

int main() {
    int n, quantum, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and queue (1 for RR, 2 for FCFS) for process %d: ", i + 1);
        scanf("%d%d%d", &arrival_time[i], &burst_time[i], &queue[i]);
        pid[i] = i + 1;
        remaining_time[i] = burst_time[i];
        completion_time[i] = 0;
    }

    printf("Enter time quantum for Round Robin queue: ");
    scanf("%d", &quantum);

    round_robin(n, quantum);
    fcfs(n);

    printf("\n%-10s%-15s%-15s%-10s%-15s%-20s%-15s\n",
           "PID", "Arrival Time", "Burst Time", "Queue",
           "Completion Time", "Turnaround Time", "Waiting Time");

    for (i = 0; i < n; i++) {
        int turnaround_time = completion_time[i] - arrival_time[i];
        int waiting_time = turnaround_time - burst_time[i];

        printf("%-10d%-15d%-15d%-10d%-15d%-20d%-15d\n",
               pid[i], arrival_time[i], burst_time[i], queue[i],
               completion_time[i], turnaround_time, waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", calculate_avg_tat(n));
    printf("Average Waiting Time: %.2f\n", calculate_avg_wt(n));

    return 0;
}
