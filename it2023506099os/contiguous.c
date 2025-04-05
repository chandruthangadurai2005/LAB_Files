#include <stdio.h>

#define MAX_BLOCKS 50
int disk[MAX_BLOCKS] = {0}; // 0 = free, 1 = allocated

void contiguousAllocation(int start, int length) {
    if (start + length > MAX_BLOCKS) {
        printf("Not enough space for contiguous allocation!\n");
        return;
    }

    for (int i = start; i < start + length; i++) {
        if (disk[i] == 1) {
            printf("Blocks already allocated, cannot allocate file.\n");
            return;
        }
    }

    for (int i = start; i < start + length; i++) {
        disk[i] = 1;
    }

    printf("File allocated contiguously from block %d to %d.\n", start, start + length - 1);
}

int main() {
    int numFiles, start, length;
    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    for (int i = 0; i < numFiles; i++) {
        printf("\nEnter start block and length for File %d: ", i + 1);
        scanf("%d %d", &start, &length);
        contiguousAllocation(start, length);
    }

    return 0;
}

