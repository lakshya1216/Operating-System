
#include <stdio.h>
#include <stdbool.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

bool isInFrame(int frames[], int frameCount, int page) {
    for (int i = 0; i < frameCount; i++)
        if (frames[i] == page)
            return true;
    return false;
}

void printFrameState(int count, int frames[], int frameCount) {
    printf("PF No. %d: ", count);
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int findLRU(int time[], int frameCount) {
    int min = time[0], pos = 0;
    for (int i = 1; i < frameCount; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int predict(int pages[], int frames[], int frameCount, int n, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void fifo(int pages[], int n, int frameCount) {
    int frames[MAX_FRAMES], front = 0, faults = 0;
    for (int i = 0; i < frameCount; i++) frames[i] = -1;
    printf("FIFO Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        if (!isInFrame(frames, frameCount, pages[i])) {
            frames[front] = pages[i];
            front = (front + 1) % frameCount;
            faults++;
            printFrameState(faults, frames, frameCount);
        }
    }
    printf("FIFO Page Faults: %d\n\n", faults);
}

void lru(int pages[], int n, int frameCount) {
    int frames[MAX_FRAMES], time[MAX_FRAMES], counter = 0, faults = 0;
    for (int i = 0; i < frameCount; i++) frames[i] = -1;
    printf("LRU Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = true;
                break;
            }
        }
        if (!found) {
            int pos = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = findLRU(time, frameCount);
            frames[pos] = pages[i];
            counter++;
            time[pos] = counter;
            faults++;
            printFrameState(faults, frames, frameCount);
        }
    }
    printf("LRU Page Faults: %d\n\n", faults);
}

void optimal(int pages[], int n, int frameCount) {
    int frames[MAX_FRAMES], faults = 0;
    for (int i = 0; i < frameCount; i++) frames[i] = -1;
    printf("Optimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        if (!isInFrame(frames, frameCount, pages[i])) {
            int pos = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = predict(pages, frames, frameCount, n, i + 1);
            frames[pos] = pages[i];
            faults++;
            printFrameState(faults, frames, frameCount);
        }
    }
    printf("Optimal Page Faults: %d\n", faults);
}

int main() {
    int pages[MAX_PAGES], n, frameCount;
    printf("Enter the number of Frames: ");
    scanf("%d", &frameCount);
    printf("Enter the Length of reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("\n");
    fifo(pages, n, frameCount);
    lru(pages, n, frameCount);
    optimal(pages, n, frameCount);
    return 0;
}
