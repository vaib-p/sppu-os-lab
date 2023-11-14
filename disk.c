#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100
#define MAX_DISTANCE 999
#define DISK_END 199


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int nearest(int requests[], int n, int head) {
    int minDist = MAX_DISTANCE, index = -1;
    for (int i = 0; i < n; i++) {
        if (requests[i] != -1 && abs(requests[i] - head) < minDist) {
            minDist = abs(requests[i] - head);
            index = i;
        }
    }
    return index;
}


void SSTF(int requests[], int n, int head) {
    int totalSeek = 0;
    printf("SSTF Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        int index = nearest(requests, n, head);
        printf("Move from %d to %d\n", head, requests[index]);
        totalSeek += abs(head - requests[index]);
        head = requests[index];
        requests[index] = -1;
    }
    printf("Total Seek Distance: %d\n", totalSeek);
}


void SCAN(int requests[], int n, int head) {
    int totalSeek = 0, headpos, j;
    printf("SCAN Disk Scheduling:\n");
  
    
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            headpos = i;
            break;
        }
    }

    for (j = headpos; j < n; j++) {
        printf("Move from %d to %d\n", head, requests[j]);
        totalSeek += abs(head - requests[j]);
        head = requests[j];
    }

   
    if (requests[j - 1] < DISK_END) {
        printf("Move from %d to %d\n", head, DISK_END);
        totalSeek += abs(head - DISK_END);
        head = DISK_END;
    }

    
    for (int i = headpos - 1; i >= 0; i--) {
        printf("Move from %d to %d\n", head, requests[i]);
        totalSeek += abs(head - requests[i]);
        head = requests[i];
    }

    printf("Total Seek Distance: %d\n", totalSeek);
}


void CLook(int requests[], int n, int head) {
    int totalSeek = 0, headpos,j;
    printf("C-Look Disk Scheduling:\n");

    for (int i = 0; i < n; i++) {
        if (requests[i] == head) {
            headpos = i;
            break;
        }
    }
    for (j = headpos; j < n; j++) {
        printf("Move from %d to %d\n", head, requests[j]);
        totalSeek += abs(head - requests[j]);
        head = requests[j];
    }
    totalSeek += abs(head - requests[0]);
    head = requests[0];
    printf("Move from %d to %d\n", requests[j-1], requests[0]);
    for (int i = 1; i < headpos; i++) {
        printf("Move from %d to %d\n", head, requests[i]);
        totalSeek += abs(head - requests[i]);
        head = requests[i];
    }
    printf("Total Seek Distance: %d\n", totalSeek);
}

int main() {
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    if (n > MAX_REQUESTS || n <= 0) {
        printf("Invalid number of requests. Exiting...\n");
        return 1;
    }

    int requests[MAX_REQUESTS];
    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);
    int sortedRequests[MAX_REQUESTS];
    for (int i = 0; i < n; i++) {
      sortedRequests[i] = requests[i];
    }
    bubbleSort(sortedRequests, n);
    SSTF(requests, n, head);
    
    

    SCAN(sortedRequests, n, head);
    CLook(sortedRequests, n, head);
    
    return 0;
}
