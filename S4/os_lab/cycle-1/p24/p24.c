/* Athul Anoop
 * Roll no: 25
 * Description: C program to simulate address translation on a page table
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

  srand(time(NULL)); // randomize seed for random number generator
  if (argc != 4) {
    printf("Usage: %s virtual_address_space_size(MB) page_size(kB) "
           "virtual_address(decimal)\n",
           argv[0]);
    exit(1);
  }
  int virtual_address_space_size = atoi(argv[1]);
  int page_size = atoi(argv[2]);
  int virtual_address = atoi(argv[3]);

  int page_count = (virtual_address_space_size * 1024) / page_size;
  int *page_table = malloc(page_count * sizeof(int));
  for (int i = 0; i < page_count; i++) {
    page_table[i] = rand() % 100 < 70 ? rand() % 10 : -1;
  }

  int page_number = virtual_address / (page_size * 1024);
  int offset = virtual_address % (page_size * 1024);

  if (page_number >= page_count) {
    printf("Invalid virtual address!\n");
  } else if (page_table[page_number] == -1) {
    printf("Page Table Miss!\n");
  } else {
    int frame_number = page_table[page_number];
    printf("Physical Address: <%d, %d>\n", frame_number, offset);
  }
  free(page_table);
  return 0;
}
