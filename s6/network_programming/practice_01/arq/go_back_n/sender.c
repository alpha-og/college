#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define TOTAL_FRAMES 10
#define WINDOW_SIZE 3
#define TIMEOUT 2
int main() {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in receiver_addr;
  socklen_t receiver_addr_len = sizeof(receiver_addr);
  memset(&receiver_addr, 0, receiver_addr_len);
  receiver_addr.sin_family = AF_INET;
  receiver_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  receiver_addr.sin_port = htons(8000);

  // timeout after 2 seconds
  struct timeval tv = {2, 0};
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

  int base = 0;
  int seq = 0;
  int ack = -1;

  while (base < TOTAL_FRAMES) {
    while (seq < base + WINDOW_SIZE && seq < TOTAL_FRAMES) {
      printf("TRANSMITTING packet %d\n", seq);
      int n_seq = htonl(seq);
      sendto(sockfd, &n_seq, sizeof(n_seq), 0,
             (struct sockaddr *)&receiver_addr, receiver_addr_len);
      seq++;
    }

    if (recvfrom(sockfd, &ack, sizeof(ack), 0,
                 (struct sockaddr *)&receiver_addr, &receiver_addr_len) > 0) {
      ack = ntohl(ack);
      if (ack >= base && ack < base + WINDOW_SIZE) {
        printf("RECEIVED ACK for packet %d\n", ack);
        base = ack + 1;
      } else {
        printf("RECEIVED out of window ACK %d\n", ack);
      }
    } else {
      printf("TIMEOUT... RETRANSMITTING window from base %d\n", base);
      seq = base;
    }
    sleep(1);
  }

  printf("All frames transmitted successfully.\n");
  close(sockfd);
  return EXIT_SUCCESS;
}
