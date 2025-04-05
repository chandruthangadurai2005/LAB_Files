#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 50
int disk[MAX_BLOCKS] = {0}; // 0 = free, 1 = allocated

typedef struct Node {
    int block;
    struct Node* next;
} Node;

void linkedAllocation(int start, int length) {
    if (start >= MAX_BLOCKS || disk[start] == 1) {
        printf("Invalid or already allocated starting block!\n");
        return;
    }

    Node *head = NULL, *temp, *last = NULL;
    int count = 0;

    printf("Linked Allocation successful from block %d. Blocks allocated: ", start);

    for (int i = start; i < MAX_BLOCKS && count < length; i++) {
        if (disk[i] == 0) {
            disk[i] = 1;
            temp = (Node*)malloc(sizeof(Node));
            temp->block = i;
            temp->next = NULL;

            if (head == NULL)
                head = temp;
            else
                last->next = temp;

            last = temp;
            count++;
            printf("%d ", i);
        }
    }

    if (count < length) {
        printf("\nNot enough free blocks for linked allocation!\n");
        return;
    }

    printf("\n");
}

int main() {
    int numFiles, start, length;
    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    for (int i = 0; i < numFiles; i++) {
        printf("\nEnter start block and length for File %d: ", i + 1);
        scanf("%d %d", &start, &length);
        linkedAllocation(start, length);
    }

    return 0;
}

