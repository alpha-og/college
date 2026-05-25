#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define TOTAL_FRAMES 10
int main() {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in receiver_addr;
  socklen_t receiver_addr_len = sizeof(receiver_addr);
  memset(&receiver_addr, 0, receiver_addr_len);
  receiver_addr.sin_family = AF_INET;
  receiver_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  receiver_addr.sin_port = htons(8000);

  struct sockaddr_in sender_addr;
  socklen_t sender_addr_len = sizeof(sender_addr);
  memset(&sender_addr, 0, sender_addr_len);

  if (bind(sockfd, (struct sockaddr *)&receiver_addr, receiver_addr_len) < 0) {
    perror("bind");
  }

  int expected = 0;
  int seq = -1;

  while (expected < TOTAL_FRAMES) {
    recvfrom(sockfd, &seq, sizeof(seq), 0, (struct sockaddr *)&sender_addr,
             &sender_addr_len);
    seq = ntohl(seq);

    if (rand() % 100 < 30) {
      printf("DROPPED packet %d\n", seq);
      continue;
    }

    if (seq == expected) {
      printf("RECEIVED packet %d\n", seq);
      int ack = htonl(seq);
      sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&sender_addr,
             sender_addr_len);
      expected++;
    } else {
      printf("DROPPED UNEXPECTED packet %d (EXPECTING %d)\n", seq, expected);
      if (expected > 0) {
        int d_ack = htonl(expected - 1);
        sendto(sockfd, &d_ack, sizeof(d_ack), 0,
               (struct sockaddr *)&sender_addr, sender_addr_len);
      }
    }
  }
  printf("All frames received successfully.\n");
  close(sockfd);
  return EXIT_SUCCESS;
}
