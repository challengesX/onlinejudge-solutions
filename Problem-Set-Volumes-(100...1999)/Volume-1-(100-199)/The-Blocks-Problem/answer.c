#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 25
int stacks[MAX_BLOCKS][MAX_BLOCKS]; 
int positions[MAX_BLOCKS];
int stackSize[MAX_BLOCKS];
void init(int n) {
    int i;
    for (i = 0; i < n; i++) {
        stacks[i][0] = i;
        positions[i] = i;
        stackSize[i] = 1;
    }
}
void printBlocks(int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d:", i);
        int j;
        for (j = 0; j < stackSize[i]; j++) {
            printf(" %d", stacks[i][j]);
        }
        printf("\n");
    }
}
void returnBlocksAbove(int block) {
    int pos = positions[block];
    while (stackSize[pos] > 0 && stacks[pos][stackSize[pos] - 1] != block) {
        int topBlock = stacks[pos][--stackSize[pos]];
        stacks[topBlock][stackSize[topBlock]++] = topBlock;
        positions[topBlock] = topBlock;
    }
}
void moveOnto(int a, int b) {
    if (positions[a] == positions[b] || a == b) return;
    returnBlocksAbove(a);
    returnBlocksAbove(b);
    int posA = positions[a];
    int posB = positions[b];
    stacks[posB][stackSize[posB]++] = a;
    stackSize[posA]--;
    positions[a] = posB;
}
void moveOver(int a, int b) {
    if (positions[a] == positions[b] || a == b) return;
    returnBlocksAbove(a);
    int posA = positions[a];
    int posB = positions[b];
    stacks[posB][stackSize[posB]++] = a;
    stackSize[posA]--;
    positions[a] = posB;
}
void pileOnto(int a, int b) {
    if (positions[a] == positions[b] || a == b) return;
    returnBlocksAbove(b);
    int posA = positions[a];
    int posB = positions[b];
    int idx;
    for (idx = 0; stacks[posA][idx] != a; idx++); 
    int i;
    for (i = idx; i < stackSize[posA]; i++) {
        int block = stacks[posA][i];
        stacks[posB][stackSize[posB]++] = block;
        positions[block] = posB;
    }
    stackSize[posA] = idx;
}
void pileOver(int a, int b) {
    if (positions[a] == positions[b] || a == b) return;
    int posA = positions[a];
    int posB = positions[b];
    int idx;
    for (idx = 0; stacks[posA][idx] != a; idx++); 
    int i;
    for (i = idx; i < stackSize[posA]; i++) {
        int block = stacks[posA][i];
        stacks[posB][stackSize[posB]++] = block;
        positions[block] = posB;
    }
    stackSize[posA] = idx;
}
int main() {
    int n;
    scanf("%d", &n);
    init(n);
    char command[5], type[5];
    int a, b;

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "quit") == 0) break;
        scanf("%d %s %d", &a, type, &b);

        if (strcmp(command, "move") == 0 && strcmp(type, "onto") == 0) {
            moveOnto(a, b);
        } else if (strcmp(command, "move") == 0 && strcmp(type, "over") == 0) {
            moveOver(a, b);
        } else if (strcmp(command, "pile") == 0 && strcmp(type, "onto") == 0) {
            pileOnto(a, b);
        } else if (strcmp(command, "pile") == 0 && strcmp(type, "over") == 0) {
            pileOver(a, b);
        }
    }
    printBlocks(n);
    return 0;
}
