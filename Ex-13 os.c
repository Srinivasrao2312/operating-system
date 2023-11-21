#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *ptr;
    int size;
} MemBlock;

// Best Fit
MemBlock *bestFit(MemBlock *blocks, int n, int memSize) {
    MemBlock *best = NULL;
    int bestDiff = 999999;
    for (int i = 0; i < n; i++) {
        if (blocks[i].size >= memSize) {
            int diff = blocks[i].size - memSize;
            if (diff < bestDiff) {
                bestDiff = diff;
                best = &blocks[i];
            }
        }
    }
    return best;
}

// Worst Fit
MemBlock *worstFit(MemBlock *blocks, int n, int memSize) {
    MemBlock *worst = NULL;
    int worstDiff = -1;
    for (int i = 0; i < n; i++) {
        if (blocks[i].size >= memSize) {
            int diff = blocks[i].size - memSize;
            if (diff > worstDiff) {
                worstDiff = diff;
                worst = &blocks[i];
            }
        }
    }
    return worst;
}

// First Fit
MemBlock *firstFit(MemBlock *blocks, int n, int memSize) {
    for (int i = 0; i < n; i++) {
        if (blocks[i].size >= memSize) {
            return &blocks[i];
        }
    }
    return NULL;
}

int main() {
    MemBlock blocks[] = {
        {NULL, 10},
        {NULL, 50},
        {NULL, 100},
        {NULL, 200}
    };

    int n = sizeof(blocks) / sizeof(blocks[0]);
    int memSize = 100;

    // Mem Block for Best Fit
    MemBlock *bestFitBlock = bestFit(blocks, n, memSize);
    if (bestFitBlock != NULL) {
        printf("Best Fit: Block of size %d allocated\n", bestFitBlock->size);
    } else {
        printf("Best Fit: No block available for allocation\n");
    }

    // Mem Block for Worst Fit
    MemBlock *worstFitBlock = worstFit(blocks, n, memSize);
    if (worstFitBlock != NULL) {
        printf("Worst Fit: Block of size %d allocated\n", worstFitBlock->size);
    } else {
        printf("Worst Fit: No block available for allocation\n");
    }

    // Mem Block for First Fit
    MemBlock *firstFitBlock = firstFit(blocks, n, memSize);
    if (firstFitBlock != NULL) {
        printf("First Fit: Block of size %d allocated\n", firstFitBlock->size);
    } else {
        printf("First Fit: No block available for allocation\n");
    }

    return 0;
}