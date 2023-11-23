#include <stdio.h>

#define MAX_BLOCKS 50

// Structure to represent a memory block
struct MemoryBlock {
    int size;
    int allocated;
};

// Function to allocate memory using worst fit algorithm
void allocateMemory(struct MemoryBlock blocks[], int numBlocks, int requestSize) {
    int worstFitIndex = -1;
    int worstFitSize = -1;

    // Find the worst fit block
    for (int i = 0; i < numBlocks; ++i) {
        if (!blocks[i].allocated && blocks[i].size >= requestSize) {
            if (worstFitIndex == -1 || blocks[i].size > worstFitSize) {
                worstFitIndex = i;
                worstFitSize = blocks[i].size;
            }
        }
    }

    // Allocate memory if a block is found
    if (worstFitIndex != -1) {
        blocks[worstFitIndex].allocated = 1;
        printf("Memory allocated successfully at block %d\n", worstFitIndex + 1);
    } else {
        printf("Memory allocation failed. No suitable block found.\n");
    }
}

// Function to display the current status of memory blocks
void displayMemoryStatus(struct MemoryBlock blocks[], int numBlocks) {
    printf("Block\tSize\tAllocated\n");
    for (int i = 0; i < numBlocks; ++i) {
        printf("%d\t%d\t%s\n", i + 1, blocks[i].size, blocks[i].allocated ? "Yes" : "No");
    }
}

int main() {
    int numBlocks, requestSize;

    // Input the number of memory blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    // Input the size of each memory block
    struct MemoryBlock blocks[MAX_BLOCKS];
    for (int i = 0; i < numBlocks; ++i) {
        printf("Enter the size of block %d: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].allocated = 0; // Initialize all blocks as unallocated
    }

    // Input the size of memory request
    printf("Enter the size of memory request: ");
    scanf("%d", &requestSize);

    // Allocate memory using worst fit algorithm
    allocateMemory(blocks, numBlocks, requestSize);

    // Display the current status of memory blocks
    displayMemoryStatus(blocks, numBlocks);

    return 0;
}
