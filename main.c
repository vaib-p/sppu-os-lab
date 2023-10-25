#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int arr[] = {12, 45, 23, 67, 10, 51, 36, 78, 3, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    
    char sortedArrayStr[1024]; 
    int offset = 0;
    for (int i = 0; i < n; i++) {
        offset += snprintf(sortedArrayStr + offset, sizeof(sortedArrayStr) - offset, "%d ", arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        

        char *execArgs[] = {"./child_process", sortedArrayStr, NULL};

        
        execve(execArgs[0], execArgs, NULL);

       
        perror("Execve failed");
        exit(1);
    } else {
      

        wait(NULL); 

        printf("Sorted Array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}

