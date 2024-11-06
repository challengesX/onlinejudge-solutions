#include <stdio.h>
#include "Math.h"
int cycle_length(int n){
    int l = 1;
    while (n != 1){
        if (n % 2 != 0){
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
        l++;
    }
    return l;
}

int max_cycle_length(int i, int j){
    int max = 0;
    for (int k = Math_Min(i, j); k <= Math_Max(i, j); k++){
        max = Math_Max(max, cycle_length(k));
    }
    return max;
}

int main() {
    int i, j;
    printf("Enter i and j or 0 for exit: ");
    scanf("%d %d", &i, &j);
    if (i == 0 || j == 0) return 0; 
    
    int maxLength = max_cycle_length(i, j);
    printf("%d %d %d\n", i, j, maxLength);
    return 0;
}
