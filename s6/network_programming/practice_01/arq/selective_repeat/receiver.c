#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define WINDOW_SIZE 3
#define TOTAL_FRAMES 10
#define TIMEOUT 2

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
    exit(EXIT_FAILURE);
  }

  int expected = 0;
  int seq = -1;
  int received[TOTAL_FRAMES] = {0};

  while (expected < TOTAL_FRAMES) {
    if (recvfrom(sockfd, &seq, sizeof(seq), 0, (struct sockaddr *)&sender_addr,
                 &sender_addr_len) > 0) {
      seq = ntohl(seq);
      if (rand() % 100 < 30) {
        printf("DROPPED (SIMULATED) frame %d\n", seq);
        continue;
      }
      printf("RECEIVED frame %d\n", seq);
      received[seq] = 1;

      seq = htonl(seq);
      sendto(sockfd, &seq, sizeof(seq), 0, (struct sockaddr *)&sender_addr,
             sender_addr_len);

      while (expected < TOTAL_FRAMES && received[expected]) {
        expected++;
      }

    } else {
      printf("TIMEOUT\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("Received all frames\n");
  close(sockfd);

  return EXIT_SUCCESS;
}
