#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>

#define MAX_PROCESSES 10

int is_schedulable(int n, float utilization) { float bound = n * (pow(2.0, 1.0 / n) - 1.0); return (utilization <= bound); }

int gcd(int a, int b) { if (b == 0) return a; return gcd(b, a % b); }

int lcm(int a, int b) { return (a * b) / gcd(a, b); }

void rate_monotonic_scheduling(int n, int exec_time[], int period[]) { int hyperperiod = period[0]; for (int i = 1; i < n; i++) { hyperperiod = lcm(hyperperiod, period[i]); }

int remaining_time[MAX_PROCESSES] = {0};
int time = 0;

printf("\nScheduling Timeline:\n");
while (time < hyperperiod) {
    int highest_priority = -1;

    for (int i = 0; i < n; i++) {
        if (time % period[i] == 0) {
            remaining_time[i] = exec_time[i];
        }
        if (remaining_time[i] > 0 && (highest_priority == -1 || period[i] < period[highest_priority])) {
            highest_priority = i;
        }
    }

    if (highest_priority != -1) {
        printf("Time %d: Task %d is executing\n", time, highest_priority + 1);
        remaining_time[highest_priority]--;
    } else {
        printf("Time %d: Idle\n", time);
    }

    time++;
}

}

int main() { int n; int exec_time[MAX_PROCESSES], period[MAX_PROCESSES];

printf("Enter the number of tasks: ");
scanf("%d", &n);

float utilization = 0.0;

for (int i = 0; i < n; i++) {
    printf("Enter execution time and period for Task %d: ", i + 1);
    scanf("%d %d", &exec_time[i], &period[i]);
    utilization += (float)exec_time[i] / period[i];
}

if (is_schedulable(n, utilization)) {
    printf("\nTasks are schedulable using Rate-Monotonic Scheduling.\n");
    rate_monotonic_scheduling(n, exec_time, period);
} else {
    printf("\nTasks are NOT schedulable using Rate-Monotonic Scheduling.\n");
}

return 0;

}
