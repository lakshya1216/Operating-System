#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 5

int hungry[MAX_PHILOSOPHERS] = {0};
int eating[MAX_PHILOSOPHERS] = {0};

void print_waiting(int n) {
    for (int i = 0; i < n; i++) {
        if (hungry[i] && !eating[i]) {
            printf("P %d is waiting\n", i + 1);
        }
    }
}

void print_granted(int n) {
    for (int i = 0; i < n; i++) {
        if (eating[i]) {
            printf("P %d is granted to eat\n", i + 1);
        }
    }
}

void finish_eating(int pos) {
    printf("P %d has finished eating\n", pos + 1);
    eating[pos] = 0;
    hungry[pos] = 0;
}

int main() {
    int total, hungry_count;
    int hungry_positions[MAX_PHILOSOPHERS];

    printf("Enter the total number of philosophers: ");
    scanf("%d", &total);

    printf("How many are hungry: ");
    scanf("%d", &hungry_count);

    for (int i = 0; i < hungry_count; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, total);
        int pos;
        scanf("%d", &pos);
        hungry[pos - 1] = 1;
    }

    int choice;
    do {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int granted = 0;

        switch (choice) {
            case 1:
                printf("Allow one philosopher to eat at any time\n");
                for (int i = 0; i < total; i++) {
                    if (hungry[i] && !eating[i]) {
                        print_waiting(total);
                        eating[i] = 1;
                        print_granted(total);
                        sleep(1);
                        finish_eating(i);
                    }
                }
                break;
            case 2:
                printf("Allow two philosophers to eat at any time\n");
                print_waiting(total);
                for (int i = 0; i < total && granted < 2; i++) {
                    if (hungry[i] && !eating[i]) {
                        eating[i] = 1;
                        granted++;
                    }
                }
                print_granted(total);
                sleep(1);
                for (int i = 0; i < total && granted > 0; i++) {
                    if (eating[i]) {
                        finish_eating(i);
                        granted--;
                    }
                }
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 3);

    return 0;
}
