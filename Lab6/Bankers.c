#include <stdio.h>
#include <stdbool.h>

int np, nr;
int alloc[10][10], max[10][10], need[10][10], avail[10];
int request[10];
int pid;

void calculateNeed() {
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nr; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafe() {
    int work[10];
    bool finish[10] = {false};
    int safeSeq[10], count = 0;

    for (int i = 0; i < nr; i++)
        work[i] = avail[i];

    while (count < np) {
        bool found = false;
        for (int i = 0; i < np; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < nr; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < nr; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;

                    printf("P%d is visited( ", i);
                    for (int j = 0; j < nr; j++) {
                        printf("%d ", work[j]);
                    }
                    printf(")\n");
                }
            }
        }

        if (!found) {
            printf("SYSTEM IS NOT IN SAFE STATE\n");
            return false;
        }
    }

    printf("SYSTEM IS IN SAFE STATE\n");
    printf("The Safe Sequence is -- ( ");
    for (int i = 0; i < np; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf(")\n");

    return true;
}

bool requestResources(int pid, int req[]) {
    for (int i = 0; i < nr; i++) {
        if (req[i] > need[pid][i]) {
            printf("Error: Request is greater than need.\n");
            return false;
        }
        if (req[i] > avail[i]) {
            printf("Resources not available.\n");
            return false;
        }
    }
    for (int i = 0; i < nr; i++) {
        avail[i] -= req[i];
        alloc[pid][i] += req[i];
        need[pid][i] -= req[i];
    }

    if (!isSafe()) {
        for (int i = 0; i < nr; i++) {
            avail[i] += req[i];
            alloc[pid][i] -= req[i];
            need[pid][i] += req[i];
        }
        printf("Request cannot be granted as it leads to unsafe state.\n");
        return false;
    }

    printf("Request can be granted.\n");
    return true;
}

int main() {
    printf("Enter number of processes -- ");
    scanf("%d", &np);

    printf("Enter number of resources -- ");
    scanf("%d", &nr);

    for (int i = 0; i < np; i++) {
        printf("Enter allocation for P%d -- ", i);
        for (int j = 0; j < nr; j++)
            scanf("%d", &alloc[i][j]);

        printf("Enter Max for P%d -- ", i);
        for (int j = 0; j < nr; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter Available Resources -- ");
    for (int i = 0; i < nr; i++)
        scanf("%d", &avail[i]);

    calculateNeed();

    printf("Enter New Request Details -- \n");
    printf("Enter pid -- ");
    scanf("%d", &pid);
    printf("Enter Request for Resources -- ");
    for (int i = 0; i < nr; i++)
        scanf("%d", &request[i]);

    requestResources(pid, request);

    printf("\n%-10s%-15s%-15s%-15s\n", "Process", "Allocation", "Max", "Need");
    for (int i = 0; i < np; i++) {
        printf("P%-9d", i);
        for (int j = 0; j < nr; j++)
            printf("%d ", alloc[i][j]);
        printf("     ");
        for (int j = 0; j < nr; j++)
            printf("%d ", max[i][j]);
        printf("     ");
        for (int j = 0; j < nr; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    return 0;
}
