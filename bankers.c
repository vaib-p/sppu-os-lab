#include <stdio.h>

#define MAX_P 10
#define MAX_R 10

int isSafe(int np, int nr, int available[MAX_R], int max[MAX_P][MAX_R], int allocation[MAX_P][MAX_R], int need[MAX_P][MAX_R]) {
    int work[MAX_R];
    int finish[MAX_P];

    // Initialize work and finish arrays
    for (int i = 0; i < nr; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < np; i++) {
        finish[i] = 0;
    }

    int safeSequence[MAX_P];
    int count = 0;

    while (count < np) {
        int found = 0;
        for (int i = 0; i < np; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < nr; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == nr) {
                    for (int k = 0; k < nr; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < np; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return 1;
}
int main() {
    int np, nr; 
    printf("Enter the number of processes: ");
    scanf("%d", &np);

    printf("Enter the number of resource types: ");
    scanf("%d", &nr);

    int max[MAX_P][MAX_R];
    int allocation[MAX_P][MAX_R];
    int available[MAX_R];

    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nr; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nr; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int j = 0; j < nr; j++) {
        scanf("%d", &available[j]);
    }

    int need[MAX_P][MAX_R];
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nr; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    isSafe(np, nr, available, max, allocation, need);

    return 0;
}

