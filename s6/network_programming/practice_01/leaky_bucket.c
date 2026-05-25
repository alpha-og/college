#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int bucket_capacity, leak_rate, packet_count;
  printf("Bucket capacity (in bytes): ");
  scanf("%d", &bucket_capacity);
  printf("Leak rate (in bytes): ");
  scanf("%d", &leak_rate);
  printf("Number of packets to transmit: ");
  scanf("%d", &packet_count);

  int bucket_utilization = 0;
  int processed_packets = 0;

  while (bucket_utilization > 0 || processed_packets < packet_count) {
    if (processed_packets < packet_count) {
      // generate random packet
      int packet_size = rand() % 3 + 5;

      // attempt to receive packet in bucket
      if (bucket_utilization + packet_size <= bucket_capacity) {

        bucket_utilization += packet_size;
        printf("PROCESSED %d bytes | Bucket: %d\n", packet_size,
               bucket_utilization);
      } else {
        // drop packet if bucket cannot accomodate the new packet
        printf("DROPPED packet with size %d | Bucket: %d\n", packet_size,
               bucket_utilization);
      }
      processed_packets++;
    }
    if (bucket_utilization > 0) {
      int bytes_transmitted =
          bucket_utilization >= leak_rate ? leak_rate : bucket_utilization;
      bucket_utilization -= bytes_transmitted;
      printf("TRANSMITTED %d bytes | Bucket: %d\n", bytes_transmitted,
             bucket_utilization);
    }
    sleep(1);
  }

  return EXIT_SUCCESS;
}
