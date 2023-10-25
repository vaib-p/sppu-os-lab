#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define data_not_filled -1
#define data_filled 0
#define data_read_client 1

typedef struct data {
    int status;
    char buff[100];
} data1;

int main() {
    int shm_id, ret_val, i = 0;
    key_t key;
    data1 *shm_ptr;

    key = ftok(".", 'A');

    shm_id = shmget(key, sizeof(data1), 0666);

    if (shm_id < 0) {
        printf("\n shmget error");
        exit(-1);
    }

    shm_ptr = (data1 *)shmat(shm_id, 0, 0);

    if ((int)shm_ptr == -1) {
        printf("\n Error for shmat");
        exit(-1);
    }

    while (shm_ptr->status != data_filled) {
        printf("\n Client is waiting for a message (status: %d)", shm_ptr->status);
        sleep(1);
    }

    printf("\n Received message from server: %s\n", shm_ptr->buff);

    shm_ptr->status = data_read_client;  // Signal that the client has read the data

    ret_val = shmdt((void *)shm_ptr);
    if (ret_val == 0) {
        printf("\n Shared memory detached");
    } else {
        printf("\n shmdt error");
    }

    return 0;
}

