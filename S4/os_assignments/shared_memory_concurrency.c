#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    key_t key = IPC_PRIVATE; // Unique key for shared memory
    int shm_id = shmget(key, sizeof(int) * 7, IPC_CREAT | 0666); // Allocate shared memory
    if (shm_id < 0) {
        perror("shmget failed");
        exit(1);
    }
    int *shared_mem = (int *)shmat(shm_id, NULL, 0);
    if (shared_mem == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }
    int *arr = shared_mem;
    int *input_completed = shared_mem+5;
    int *sorting_completed = shared_mem+6;
    *input_completed = 0;
    *sorting_completed = 0;
    pid_t pid = fork();
    if (pid < 0) {
        printf("Error in forking process\n");
    }
    else if (pid > 0) {
        if (*input_completed == 0) {
            for (int i = 0; i < 5; i++) {
                printf("Input value: ");
                scanf("%d", &arr[i]);
            }
            printf("Input completed\n");
            for (int i = 0; i < 5; i++) {
                printf("%d ", arr[i]);
            }
            *input_completed = 1;
        } 
        while (*sorting_completed == 0) {
            sleep(1);
        }
        printf("Sorted array: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        shmdt(shared_mem);
        shmctl(shm_id, IPC_RMID, NULL);
    }
    else if (pid == 0) {
        while (*sorting_completed == 0) {
            if (*input_completed == 1) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5-i-1; j++) {
                        if (arr[j] < arr[j+1]) {
                            int temp = arr[j];
                            arr[j] = arr[j+1];
                            arr[j+1] = temp;
                        }
                    }
                }
                *sorting_completed = 1;
            } else {
                sleep(1);
            } 
        }
        
        shmdt(shared_mem);
    }


}
