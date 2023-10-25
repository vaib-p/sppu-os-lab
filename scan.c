#include <stdio.h>
#include <stdlib.h>

int main() {
    int request[20], n, headpos, sstf[20];
    printf("Enter the number of requests:\t");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter request %d:\t", i + 1);
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position:\t");
    scanf("%d", &headpos);

    sstf[0] = headpos;

    for (int i = 0; i < n; i++) {
        int min = 999;  
        int minIndex = -1;
        int direction = 1;  // 1 for moving right, -1 for moving left

        for (int j = 0; j < n; j++) {
            if (request[j] != -1) {
                int seekTime = abs(headpos - request[j]);
                if (seekTime < min && ((request[j] - headpos) * direction >= 0)) {
                    min = seekTime;
                    minIndex = j;
                }
            }
        }

        if (minIndex == -1) {
            // If no request is found in the current direction, change direction
            direction = -direction;
            continue;
        }

        sstf[i] = request[minIndex];
        headpos = request[minIndex];
        request[minIndex] = -1;  
    }

    for (int i = 0; i < n; i++) {
        printf("%d\t", sstf[i]);
    }

    return 0;
}

