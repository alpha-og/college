/*
 * Athul Anoop
 * Roll no: 25
 * Description:
 *Simulate the disk-scheduling algorithms as follows:\\
a) FCFS\\
b) SCAN\\
c) LOOK\\
d) CSCAN\\
Your program will service a disk with 5,000 cylinders numbered 0 to 4,999. The
program will generate a random series of 10 cylinder requests and service them
according to each of the algorithms listed earlier. The program should be
invoked with the initial position of the disk head and the last request served
as command line arguments and should report the total number of head movements
required by each algorithm.\\
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CYLINDERS 5000
#define REQUEST_SIZE 10

void reset();
void move_head(int destination);
void schedule_fcfs();
void schedule_scan();
void schedule_look();
void schedule_cscan();

int head_movement_count = 0;
int current_position = 0;
int direction = 1;
int requests[REQUEST_SIZE] = {0};
int initial_position = 0;
int last_request_served = 0;

int main(int argc, char *argv[]) {
  /* srand(time(NULL)); // randomize seed for random number generator */

  if (argc != 3) {
    printf("Usage: %s initial_position last_request_served\n", argv[0]);
    exit(1);
  }
  initial_position = atoi(argv[1]);
  last_request_served = atoi(argv[2]);
  if (initial_position < 0 || initial_position > CYLINDERS) {
    printf("Invalid value of initial_position\n");
    exit(1);
  }
  if (last_request_served < 0 || last_request_served > CYLINDERS) {
    printf("Invalid value of last_request_served\n");
    exit(1);
  }

  // generate random cylinder requests
  printf("Cylinder requests: ");
  for (int i = 0; i < REQUEST_SIZE; i++) {
    requests[i] = rand() % CYLINDERS;
    printf("%d,", requests[i]);
  }
  printf("\n");

  // service requestions using FCFS
  schedule_fcfs();
  for (int i = 0; i < REQUEST_SIZE; i++) {
    for (int j = 0; j < REQUEST_SIZE - i - 1; j++) {
      if (requests[j] > requests[j + 1]) {
        int tmp = requests[j];
        requests[j] = requests[j + 1];
        requests[j + 1] = tmp;
      }
    }
  }
  printf("Sorted requests: ");
  for (int i = 0; i < REQUEST_SIZE; i++) {
    printf("%d,", requests[i]);
  }
  printf("\n");

  schedule_scan();

  return 0;
}

void reset() {
  head_movement_count = 0;
  direction = 1;
  current_position = initial_position;
}

void move_head(int destination) {
  if (current_position > destination) {
    head_movement_count += current_position - destination;
    current_position = destination;
  } else if (current_position < destination) {
    head_movement_count += destination - current_position;
    current_position = destination;
  }
}

void schedule_fcfs() {
  reset();
  for (int i = 0; i < REQUEST_SIZE; i++) {
    move_head(requests[i]);
  }
  printf("Head movements for FCFS: %d\n", head_movement_count);
}

void schedule_scan() {
  reset();
  if (last_request_served <= current_position)
    direction = 1;
  else
    direction = -1;
  int tmp = 0;
  int completed = 0;
  for (int i = 0; i < REQUEST_SIZE; i++) {
    if (current_position <= requests[i]) {
      tmp = i;
      break;
    }
  }
  int next_request = tmp;
  while (completed < REQUEST_SIZE) {
    if (direction == 1) {
      if (next_request < REQUEST_SIZE) {
        move_head(requests[next_request++]);
        printf("Servicing (right) %d\n", requests[next_request]);
        completed++;
      } else {
        printf("Moving head to last cylinder\n");
        move_head(CYLINDERS - 1);
        next_request = tmp - 1;
        direction = -1;
      }
    } else {
      if (next_request >= 0) {
        move_head(requests[next_request--]);
        printf("Servicing (left) %d\n", requests[next_request]);
        completed++;
      } else {
        printf("Moving head to first cylinder\n");
        move_head(0);
        direction = 1;
      }
    }
  }

  printf("Head movements for SCAN: %d\n", head_movement_count);
}
void schedule_look() {}
void schedule_cscan() {}
