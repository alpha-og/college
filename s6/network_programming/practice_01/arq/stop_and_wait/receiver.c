#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_FRAMES 10
#define BUFFER_SIZE 32
int main() {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in receiver_addr, sender_addr;
  socklen_t receiver_size = sizeof(receiver_addr);
  socklen_t sender_size = sizeof(sender_addr);
  memset(&receiver_addr, 0, receiver_size);
  memset(&sender_addr, 0, sender_size);
  receiver_addr.sin_family = AF_INET;
  receiver_addr.sin_addr.s_addr = INADDR_ANY;
  receiver_addr.sin_port = htons(8085);

  if (bind(sockfd, (struct sockaddr *)&receiver_addr, receiver_size) < 0) {
    perror("bind");
  };

  int expected = 0;
  int seq = -1;

  while (expected < TOTAL_FRAMES) {
    recvfrom(sockfd, &seq, sizeof(seq), 0, (struct sockaddr *)&sender_addr,
             &sender_size);
    seq = ntohl(seq);

    if (rand() % 100 < 40)
      continue;

    if (seq == expected) {
      expected++;
      printf("RECEIVED packet %d\n", seq);
      seq = htonl(seq);
      sendto(sockfd, &seq, sizeof(seq), 0, (struct sockaddr *)&sender_addr,
             sender_size);
    } else {

      seq = htonl(seq);
      printf("DROPPED packet %d\n", seq);
    }
  }

  return EXIT_SUCCESS;
}
