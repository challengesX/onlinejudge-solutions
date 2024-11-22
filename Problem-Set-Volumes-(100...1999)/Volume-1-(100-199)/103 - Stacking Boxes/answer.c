#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int index;
    int *dimensions;
} Box;

int n;

int compareDimensions(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int canNest(Box *boxA, Box *boxB) {
    int i;
    for (i = 0; i < n; i++) {
        if (boxA->dimensions[i] >= boxB->dimensions[i]) {
            return 0;
        }
    }
    return 1;
}

int compareBoxes(const void *a, const void *b) {
    Box *boxA = (Box *)a;
    Box *boxB = (Box *)b;
    for (int i = 0; i < n; i++) {
        if (boxA->dimensions[i] != boxB->dimensions[i]) {
            return boxA->dimensions[i] - boxB->dimensions[i];
        }
    }
    return 0;
}

void findLongestNestingSequence() {
    int k;
    if (scanf("%d %d", &k, &n) != 2) {
        fprintf(stderr, "Invalid input format. Expected two integers.\n");
        exit(EXIT_FAILURE);
    }

    Box *boxes = (Box *)malloc(k * sizeof(Box));
    if (boxes == NULL) {
        fprintf(stderr, "Memory allocation failed for boxes.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < k; i++) {
        boxes[i].index = i + 1;
        boxes[i].dimensions = (int *)malloc(n * sizeof(int));
        if (boxes[i].dimensions == NULL) {
            fprintf(stderr, "Memory allocation failed for box dimensions.\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < n; j++) {
            if (scanf("%d", &boxes[i].dimensions[j]) != 1) {
                fprintf(stderr, "Invalid input for box dimensions.\n");
                exit(EXIT_FAILURE);
            }
        }
        qsort(boxes[i].dimensions, n, sizeof(int), compareDimensions);
    }
    qsort(boxes, k, sizeof(Box), compareBoxes);

    int *dp = (int *)calloc(k, sizeof(int));
    int *prev = (int *)calloc(k, sizeof(int));
    if (dp == NULL || prev == NULL) {
        fprintf(stderr, "Memory allocation failed for dp or prev arrays.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < k; i++) {
        dp[i] = 1;
        prev[i] = -1;
    }

    for (int u = 0; u < k; u++) {
        for (int v = u + 1; v < k; v++) {
            if (canNest(&boxes[u], &boxes[v])) {
                if (dp[u] + 1 > dp[v]) {
                    dp[v] = dp[u] + 1;
                    prev[v] = u;
                }
            }
        }
    }
    int maxLength = 0, maxIndex = -1;
    for(int u=1;u<k;u++){
        if (dp[u] >= maxLength) {
            maxLength = dp[u];
            maxIndex = u;
        }
    }

    printf("%d\n", maxLength);

    int *sequence = (int *)malloc(maxLength * sizeof(int));
    if (sequence == NULL) {
        fprintf(stderr, "Memory allocation failed for sequence array.\n");
        exit(EXIT_FAILURE);
    }

    int idx = 0;
    while (maxIndex != -1) {
        sequence[idx++] = boxes[maxIndex].index;
        maxIndex = prev[maxIndex];
    }

    for (int i = maxLength - 1; i >= 0; i--) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    // Free allocated memory
    for (int i = 0; i < k; i++) {
        free(boxes[i].dimensions);
    }
    free(boxes);
    free(dp);
    free(prev);
    free(sequence);
}

int main() {
    printf("Enter input (end with EOF):\n");
    findLongestNestingSequence();
    return 0;
}
