#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <sorted_array>\n", argv[0]);
        return 1;
    }

    char *sortedArray = argv[1];
    int numbers[100]; 
    int n = 0;

    char *token = strtok(sortedArray, " ");
    while (token != NULL) {
        numbers[n++] = atoi(token);
        token = strtok(NULL, " ");
    }

    printf("Reversed Array of Sorted Array: ");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}

