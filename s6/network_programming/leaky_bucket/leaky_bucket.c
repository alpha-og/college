#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  srand(time(NULL));

  int bucket_size = -1;
  int bucket_utilization = 0;
  int rate = -1;
  int packet_count = -1;

  int opt;

  while ((opt = getopt(argc, argv, "b:r:p:")) != -1) {
    switch (opt) {
    case 'b':
      bucket_size = atoi(optarg);
      break;
    case 'r':
      rate = atoi(optarg);
      break;
    case 'p':
      packet_count = atoi(optarg);
      break;
    default:
      fprintf(stderr, "Usage: %s -b <bucket_size> -r <rate> -p <packet_count>",
              argv[0]);
      return EXIT_FAILURE;
    }
  }

  fprintf(stdout, "Bucket Size: %d | Leak Rate: %d | Packet Count: %d\n\n",
          bucket_size, rate, packet_count);

  // generate packets
  int *packets = calloc(packet_count, sizeof(int));
  for (int i = 0; i < packet_count; i++) {
    packets[i] = (rand() % 10 + 1);
  }
  int i = 0;

  while (i < packet_count || bucket_utilization > 0) {
    i++;
    if (i < packet_count) {
      if (bucket_utilization + packets[i] < bucket_size) {
        bucket_utilization += packets[i];
        fprintf(stdout,
                "Packet %d of size %d received in bucket | Bucket Utilization: "
                "%d\n",
                i, packets[i], bucket_utilization);
      } else {
        fprintf(stdout, "Packet %d of size %d overflowed\n", i, packets[i]);
      }
    }

    sleep(1);
    if (bucket_utilization <= rate) {
      fprintf(stdout, "Transmitting %d bytes\n", bucket_utilization);
      bucket_utilization = 0;
    } else {
      fprintf(stdout, "Transmitting %d bytes\n", rate);
      bucket_utilization -= rate;
    }
  }
  return EXIT_SUCCESS;
}
