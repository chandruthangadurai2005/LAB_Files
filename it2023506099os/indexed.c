#include <stdio.h>

#define MAX_BLOCKS 50
int disk[MAX_BLOCKS] = {0}; // 0 = free, 1 = allocated

void indexedAllocation(int start, int length) {
    if (start >= MAX_BLOCKS || disk[start] == 1) {
        printf("Invalid or already allocated starting block!\n");
        return;
    }

    int dataBlocks[length], count = 0;
    disk[start] = 1; // Mark index block

    for (int i = 0; i < MAX_BLOCKS && count < length; i++) {
        if (disk[i] == 0) {
            disk[i] = 1;
            dataBlocks[count++] = i;
        }
    }

    if (count < length) {
        printf("Not enough free blocks for indexed allocation!\n");
        return;
    }

    printf("Indexed Allocation successful.\nIndex Block: %d\nData Blocks: ", start);
    for (int i = 0; i < length; i++)
        printf("%d ", dataBlocks[i]);
    printf("\n");
}

int main() {
    int numFiles, start, length;
    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    for (int i = 0; i < numFiles; i++) {
        printf("\nEnter start block and length for File %d: ", i + 1);
        scanf("%d %d", &start, &length);
        indexedAllocation(start, length);
    }

    return 0;
}

