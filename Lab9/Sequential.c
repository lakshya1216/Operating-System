#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

int disk[MAX_BLOCKS];  // 0 = free, 1 = allocated

typedef struct {
    int startBlock;
    int length;
} File;

void initializeDisk() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i] = 0; // All blocks initially free
    }
}

int allocateSequential(File *f, int length) {
    f->length = length;

    for (int i = 0; i <= MAX_BLOCKS - length; i++) {
        int found = 1;
        for (int j = 0; j < length; j++) {
            if (disk[i + j] != 0) {
                found = 0;
                break;
            }
        }

        if (found) {
            f->startBlock = i;
            for (int j = 0; j < length; j++) {
                disk[i + j] = 1;
            }
            return 1; // Success
        }
    }
    return 0; // Failed
}

void displayFile(File f, int fileIndex) {
    printf("File %d: Start Block = %d, Length = %d, Blocks = [", fileIndex, f.startBlock, f.length);
    for (int i = 0; i < f.length; i++) {
        printf("%d", f.startBlock + i);
        if (i < f.length - 1)
            printf(", ");
    }
    printf("]\n");
}

int main() {
    int n;
    printf("Enter the number of files: ");
    scanf("%d", &n);

    File files[n];

    initializeDisk();

    for (int i = 0; i < n; i++) {
        int length;
        printf("Enter the length (number of blocks) for file %d: ", i + 1);
        scanf("%d", &length);

        if (!allocateSequential(&files[i], length)) {
            printf("Unable to allocate space for file %d. Not enough contiguous blocks.\n", i + 1);
        } else {
            displayFile(files[i], i + 1);
        }
    }

    return 0;
}
