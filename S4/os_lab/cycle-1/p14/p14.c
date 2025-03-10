/* Athul Anoop
 * Roll no: 25
 * Description: C program to simulate paging algorithms (assumption: demand
 * paging is utilized) the child process
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_REF_STRING_SIZE 10
#define PAGE_COUNT 5
#define FRAME_COUNT 3

void simulate_fifo();
int search(int *frames, int item);
void init_frames(int *frames);

void simulate_lru();
void simulate_lfu();

int page_ref_strings[PAGE_REF_STRING_SIZE] = {0};

int main() {
  srand(time(NULL));
  printf("\nPage ref string: ");
  for (int i = 0; i < PAGE_REF_STRING_SIZE; i++) {
    page_ref_strings[i] = rand() % PAGE_COUNT;
    printf("%d ", page_ref_strings[i]);
  }
  simulate_fifo();
  simulate_lru();
  simulate_lfu();
  return 0;
}

void init_frames(int *frames) {
  for (int i = 0; i < FRAME_COUNT; i++) {
    frames[i] = -1;
  }
}

void simulate_fifo() {
  int page_faults = 0;
  int frames[FRAME_COUNT];
  init_frames(frames);
  int rear = 0;
  for (int i = 0; i < PAGE_REF_STRING_SIZE; i++) {
    int current_page = page_ref_strings[i];
    if (search(frames, current_page) == -1) {
      frames[rear] = current_page;
      rear = (rear + 1) % FRAME_COUNT;
      page_faults++;
    }
  }
  printf("\nFIFO: %d page faults", page_faults);
}

void simulate_lru() {
  int page_faults = 0;
  int frames[FRAME_COUNT];
  init_frames(frames);
  int top = -1;
  for (int i = 0; i < PAGE_REF_STRING_SIZE; i++) {
    int current_page = page_ref_strings[i];
    int existing = search(frames, current_page);
    if (existing == -1) {
      int cur = 0;
      while (top == FRAME_COUNT - 1 && cur < top) {
        frames[cur] = frames[cur + 1];
        cur++;
      }
      if (top < FRAME_COUNT - 1)
        top++;
      frames[top] = current_page;
      page_faults++;
    } else {
      while (existing < top) {
        int tmp = frames[existing];
        frames[existing] = frames[existing + 1];
        frames[existing + 1] = tmp;
        existing++;
      }
    }
  }
  printf("\nLRU: %d page faults", page_faults);
}

void simulate_lfu() {
  int page_faults = 0;
  int frames[FRAME_COUNT];
  int page_usage[PAGE_COUNT] = {0};
  init_frames(frames);
  int rear = -1;
  for (int i = 0; i < PAGE_REF_STRING_SIZE; i++) {
    int current_page = page_ref_strings[i];
    int existing = search(frames, current_page);
    if (existing == -1) {
      if (rear < FRAME_COUNT - 1) {
        rear++;
        frames[rear] = current_page;
      } else {
        int least_used = 0;
        for (int j = 1; j < FRAME_COUNT; j++) {
          if (page_usage[frames[j]] < page_usage[least_used])
            least_used = frames[j];
        }
        frames[least_used] = current_page;
      }
      page_faults++;
      page_usage[current_page] += 1;
    }
  }
  printf("\nLFU: %d page faults", page_faults);
}

int search(int *frames, int item) {
  for (int i = 0; i < FRAME_COUNT; i++) {
    if (frames[i] == item)
      return i;
  }
  return -1;
}
