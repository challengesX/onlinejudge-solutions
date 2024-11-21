#include <stdio.h>
#include <string.h>
#define INF 2147483647
int calculate_moves(int bins[3][3], char colors[3]) {
    int moves = 0,i,j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (colors[i] != "BGC"[j]) {
                moves += bins[i][j];
            }
        }
    }
    return moves;
}

int main() {
    int bins[3][3],min_moves, moves,i;
    char colors[] = "BCG";
    char best_assignment[4];
    while (scanf("%d %d %d %d %d %d %d %d %d", 
                  &bins[0][0], &bins[0][1], &bins[0][2], 
                  &bins[1][0], &bins[1][1], &bins[1][2], 
                  &bins[2][0], &bins[2][1], &bins[2][2]) == 9) {
        
        min_moves = INF;
        char assignments[6][4] = {
            "BCG", "BGC", "CBG", "CGB", "GBC", "GCB"
        };
        for (i = 0; i < 6; i++) {
            moves = calculate_moves(bins, assignments[i]);
            if (moves < min_moves || (moves == min_moves && strcmp(assignments[i], best_assignment) < 0)) {
                min_moves = moves;
                strcpy(best_assignment, assignments[i]);
            }
        }
        printf("%s %d\n", best_assignment, min_moves);
    }

    return 0;
}
