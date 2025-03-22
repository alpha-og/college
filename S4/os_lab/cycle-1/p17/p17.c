/*
 * Athul Anoop
 * Roll no: 25
 * Description: C program to simulate disk scheduling algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CYLINDERS 5000
#define REQUEST_SIZE 10
#define DIRECTION_UP 1
#define DIRECTION_DOWN 0

void reset();
void move_head(int destination);
int update_direction();
int *update_next_requests();
void schedule_fcfs();
void schedule_scan();
void schedule_look();
void schedule_cscan();

int head_movement_count = 0;
int current_position = 0;
int direction = DIRECTION_UP;
int requests[REQUEST_SIZE] = {0};
int next_requests[2] = {0};
int initial_position = 0;
int last_request_served = 0;

int main(int argc, char *argv[]) {
  srand(time(NULL)); // randomize seed for random number generator

  if (argc != 3) {
    printf("Usage: %s initial_position last_request_served\n", argv[0]);
    exit(1);
  }
  initial_position = atoi(argv[1]);
  last_request_served = atoi(argv[2]);
  if (initial_position < 0 || initial_position >= CYLINDERS) {
    printf("Invalid value of initial_position\n");
    exit(1);
  }
  if (last_request_served < 0 || last_request_served >= CYLINDERS) {
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

  // service requests using FCFS
  schedule_fcfs();

  // sort requests
  for (int i = 0; i < REQUEST_SIZE; i++) {
    for (int j = 0; j < REQUEST_SIZE - i - 1; j++) {
      if (requests[j] > requests[j + 1]) {
        int tmp = requests[j];
        requests[j] = requests[j + 1];
        requests[j + 1] = tmp;
      }
    }
  }
  printf("\nSorted requests: ");
  for (int i = 0; i < REQUEST_SIZE; i++) {
    printf("%d,", requests[i]);
  }
  printf("\n");

  // service requests using SCAN
  schedule_scan();
  // service requests using LOOK
  schedule_look();
  // service requests using CSCAN
  schedule_cscan();

  return 0;
}

void reset() {
  printf("\nResetting disk state\n");
  head_movement_count = 0;
  direction = DIRECTION_UP;
  current_position = initial_position;
  printf("Head movements = %d\n", head_movement_count);
  printf("Direction: %s\n", direction == DIRECTION_UP ? "UP" : "DOWN");
  printf("Current position = %d\n", initial_position);
}

void move_head(int destination) {
  printf("Moving head to %d\n", destination);
  if (current_position > destination) {
    head_movement_count += current_position - destination;
    current_position = destination;
  } else if (current_position < destination) {
    head_movement_count += destination - current_position;
    current_position = destination;
  }
}

int update_direction() {
  if (last_request_served <= current_position)
    direction = DIRECTION_UP;
  else
    direction = DIRECTION_DOWN;
  return direction;
}

int *update_next_requests() {
  for (int i = 0; i < REQUEST_SIZE; i++) {
    if (current_position <= requests[i]) {
      next_requests[1] = i;
      if (i > 0)
        next_requests[0] = i - 1;
      break;
    }
  }

  // next[0] corresponds to next request in the downward direction
  // next[1] corresponds to next request in the upward direction
  return next_requests;
}

void schedule_fcfs() {
  reset();
  printf("\nSimulating FFCFS disk scheduling algorithm\n");
  for (int i = 0; i < REQUEST_SIZE; i++) {
    move_head(requests[i]);
  }
  printf("Head movements for FCFS: %d\n", head_movement_count);
}

void schedule_scan() {
  reset();
  printf("\nSimulating SCAN disk scheduling algorithm\n");
  update_direction();
  update_next_requests();
  int next = next_requests[direction];
  int completed = 0;
  while (completed < REQUEST_SIZE) {
    if (direction == DIRECTION_UP) {
      if (next < REQUEST_SIZE) {
        move_head(requests[next++]);
        completed++;
      } else {
        move_head(CYLINDERS - 1);
        direction = DIRECTION_DOWN;
        next = next_requests[direction];
      }
    } else {
      if (next >= 0) {
        move_head(requests[next--]);
        completed++;
      } else {
        move_head(0);
        direction = DIRECTION_UP;
        next = next_requests[direction];
      }
    }
  }

  printf("Head movements for SCAN: %d\n", head_movement_count);
}
void schedule_look() {
  reset();
  printf("\nSimulating LOOK disk scheduling algorithm\n");
  update_direction();
  update_next_requests();
  int next = next_requests[direction];
  int completed = 0;

  while (completed < REQUEST_SIZE) {
    if (direction == DIRECTION_UP) {
      if (next < REQUEST_SIZE) {
        move_head(requests[next++]);
        completed++;
      } else {
        direction = DIRECTION_DOWN;
        next = next_requests[direction];
      }
    } else {
      if (next >= 0) {
        move_head(requests[next--]);
        completed++;
      } else {
        direction = DIRECTION_UP;
        next = next_requests[direction];
      }
    }
  }

  printf("Head movements for LOOK: %d\n", head_movement_count);
}
void schedule_cscan() {
  reset();

  printf("\nSimulating CSCAN disk scheduling algorithm\n");
  update_direction();
  update_next_requests();
  int next = next_requests[direction];
  int completed = 0;

  while (completed < REQUEST_SIZE) {
    if (direction == DIRECTION_UP) {
      if (next < REQUEST_SIZE) {
        move_head(requests[next++]);
        completed++;
      } else {
        move_head(CYLINDERS - 1);
        move_head(0);
        next = 0;
      }
    } else {
      if (next >= 0) {
        move_head(requests[next--]);
        completed++;
      } else {
        move_head(0);
        move_head(CYLINDERS - 1);
        next = REQUEST_SIZE - 1;
      }
    }
  }

  printf("Head movements for CSCAN: %d\n", head_movement_count);
}
