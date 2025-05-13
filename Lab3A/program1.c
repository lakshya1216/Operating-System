#include <stdio.h>
#define MAX 10

int pid[MAX], arrival_time[MAX], burst_time[MAX], priority[MAX], queue[MAX], remaining_time[MAX];
int completion_time[MAX];  // Declare completion_time array

void fcfs(int n, int queue_type) {
    int time = 0, i;
    for (i = 0; i < n; i++) {
        if (queue[i] == queue_type && remaining_time[i] > 0) {
            if (time < arrival_time[i]) {  // If the CPU is idle, fast-forward time
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
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and queue (1 for System, 2 for User) for process %d: ", i + 1);
        scanf("%d%d%d", &arrival_time[i], &burst_time[i], &queue[i]);
        pid[i] = i + 1;
        remaining_time[i] = burst_time[i];
    }

    fcfs(n, 1);

    fcfs(n, 2);

    // Display the table with results
    printf("\n%-10s%-15s%-15s%-10s%-20s%-20s%-15s\n",
           "PID", "Arrival Time", "Burst Time", "Queue",
           "Completion Time", "Turnaround Time", "Waiting Time");

    for (i = 0; i < n; i++) {
        int turnaround_time = completion_time[i] - arrival_time[i];
        int waiting_time = turnaround_time - burst_time[i];

        printf("%-10d%-15d%-15d%-10d%-20d%-20d%-15d\n",
               pid[i], arrival_time[i], burst_time[i], queue[i],
               completion_time[i], turnaround_time, waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", calculate_avg_tat(n));
    printf("Average Waiting Time: %.2f\n", calculate_avg_wt(n));

    return 0;
}
