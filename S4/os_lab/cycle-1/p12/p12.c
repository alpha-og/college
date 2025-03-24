/*
 * Athul Anoop
 * Roll no: 25
 * Description: C program to simulate various scheduling algorithms
 */

#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
  int id, arrival, burst, priority, remaining, completion, waiting, turnaround;
} Process;

void sort_by_arrival(Process p[], int n) {
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i - 1; j++)
      if (p[j].arrival > p[j + 1].arrival) {
        Process temp = p[j];
        p[j] = p[j + 1];
        p[j + 1] = temp;
      }
}

float fcfs(Process p[], int n) {
  int current_time = 0, total_waiting = 0;
  for (int i = 0; i < n; i++) {
    p[i].completion =
        (p[i].arrival > current_time ? p[i].arrival : current_time) +
        p[i].burst;
    p[i].turnaround = p[i].completion - p[i].arrival;
    p[i].waiting = p[i].turnaround - p[i].burst;
    total_waiting += p[i].waiting;
    current_time = p[i].completion;
  }
  float avg_waiting = (float)total_waiting / n;
  printf("FCFS Avg Waiting Time: %.2f\n", avg_waiting);
  return avg_waiting;
}

float sjf(Process p[], int n) {
  int completed = 0, current_time = 0, min_idx, total_waiting = 0;
  int is_completed[MAX] = {0};

  while (completed < n) {
    min_idx = -1;
    int min_burst = INT_MAX;
    for (int i = 0; i < n; i++)
      if (!is_completed[i] && p[i].arrival <= current_time &&
          p[i].burst < min_burst) {
        min_burst = p[i].burst;
        min_idx = i;
      }

    if (min_idx == -1) {
      current_time++;
      continue;
    }

    p[min_idx].completion = current_time + p[min_idx].burst;
    p[min_idx].turnaround = p[min_idx].completion - p[min_idx].arrival;
    p[min_idx].waiting = p[min_idx].turnaround - p[min_idx].burst;
    total_waiting += p[min_idx].waiting;
    is_completed[min_idx] = 1;
    completed++;
    current_time = p[min_idx].completion;
  }
  float avg_waiting = (float)total_waiting / n;
  printf("SJF Avg Waiting Time: %.2f\n", avg_waiting);
  return avg_waiting;
}

float priority_scheduling(Process p[], int n) {
  int completed = 0, current_time = 0, min_idx, total_waiting = 0;
  int is_completed[MAX] = {0};

  while (completed < n) {
    min_idx = -1;
    int max_priority = INT_MIN;
    for (int i = 0; i < n; i++)
      if (!is_completed[i] && p[i].arrival <= current_time &&
          p[i].priority > max_priority) {
        max_priority = p[i].priority;
        min_idx = i;
      }

    if (min_idx == -1) {
      current_time++;
      continue;
    }

    p[min_idx].completion = current_time + p[min_idx].burst;
    p[min_idx].turnaround = p[min_idx].completion - p[min_idx].arrival;
    p[min_idx].waiting = p[min_idx].turnaround - p[min_idx].burst;
    total_waiting += p[min_idx].waiting;
    is_completed[min_idx] = 1;
    completed++;
    current_time = p[min_idx].completion;
  }
  float avg_waiting = (float)total_waiting / n;
  printf("Priority Avg Waiting Time: %.2f\n", avg_waiting);
  return avg_waiting;
}

float round_robin(Process p[], int n, int quantum) {
  int current_time = 0, completed = 0, total_waiting = 0;
  int remaining_time[MAX];

  for (int i = 0; i < n; i++)
    remaining_time[i] = p[i].burst;

  while (completed < n) {
    for (int i = 0; i < n; i++) {
      if (remaining_time[i] > 0) {
        int exec_time =
            (remaining_time[i] > quantum) ? quantum : remaining_time[i];
        current_time += exec_time;
        remaining_time[i] -= exec_time;

        if (remaining_time[i] == 0) {
          p[i].completion = current_time;
          p[i].turnaround = p[i].completion - p[i].arrival;
          p[i].waiting = p[i].turnaround - p[i].burst;
          total_waiting += p[i].waiting;
          completed++;
        }
      }
    }
  }
  float avg_waiting = (float)total_waiting / n;
  printf("Round Robin Avg Waiting Time: %.2f\n", avg_waiting);
  return avg_waiting;
}

float srtf(Process p[], int n) {
  int remaining_time[MAX], completed = 0, current_time = 0, min_idx,
                           total_waiting = 0;
  for (int i = 0; i < n; i++)
    remaining_time[i] = p[i].burst;

  while (completed < n) {
    min_idx = -1;
    int min_remaining = INT_MAX;
    for (int i = 0; i < n; i++)
      if (p[i].arrival <= current_time && remaining_time[i] > 0 &&
          remaining_time[i] < min_remaining) {
        min_remaining = remaining_time[i];
        min_idx = i;
      }

    if (min_idx == -1) {
      current_time++;
      continue;
    }

    remaining_time[min_idx]--;
    current_time++;
    if (remaining_time[min_idx] == 0) {
      completed++;
      p[min_idx].completion = current_time;
      p[min_idx].turnaround = p[min_idx].completion - p[min_idx].arrival;
      p[min_idx].waiting = p[min_idx].turnaround - p[min_idx].burst;
      total_waiting += p[min_idx].waiting;
    }
  }
  float avg_waiting = (float)total_waiting / n;
  printf("SRTF Avg Waiting Time: %.2f\n", avg_waiting);
  return avg_waiting;
}

int main() {
  int n, quantum = 3;
  Process p[MAX];

  printf("Enter number of processes: ");
  scanf("%d", &n);
  printf("Enter Process ID, Arrival Time, Burst Time, Priority:\n");
  for (int i = 0; i < n; i++)
    scanf("%d %d %d %d", &p[i].id, &p[i].arrival, &p[i].burst, &p[i].priority);

  sort_by_arrival(p, n);
  float times[] = {fcfs(p, n), sjf(p, n), priority_scheduling(p, n),
                   round_robin(p, n, quantum), srtf(p, n)};
  char *algorithms[] = {"FCFS", "SJF", "Priority", "Round Robin", "SRTF"};

  int best_idx = 0;
  for (int i = 1; i < 5; i++)
    if (times[i] < times[best_idx])
      best_idx = i;
  printf("Best Scheduling Algorithm: %s with Avg Waiting Time: %.2f\n",
         algorithms[best_idx], times[best_idx]);
  return 0;
}
