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

  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  memset(&addr, 0, addr_len);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(8000);

  struct timeval tv = {TIMEOUT, 0};

  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

  int base = 0;
  int seq = 0;
  int ack = -1;
  int acked[TOTAL_FRAMES] = {0};

  while (base < TOTAL_FRAMES) {
    while (seq < base + WINDOW_SIZE && seq < TOTAL_FRAMES) {
      printf("TRANSMITTING frames %d\n", seq);
      int n_seq = htonl(seq);
      sendto(sockfd, &n_seq, sizeof(n_seq), 0, (struct sockaddr *)&addr,
             addr_len);
      seq++;
    }

    if (recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&addr,
                 &addr_len) > 0) {
      ack = ntohl(ack);
      printf("RECEIVED ACK for frame %d\n", ack);
      if (!acked[ack]) {
        acked[ack] = 1;
        while (acked[base]) {
          base++;
        }
      }
    } else {
      printf("TIMEOUT... RETRANSMITTING unacknowledged frames in window\n");
      for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
        if (acked[i])
          continue;
        int n_seq = htonl(i);
        sendto(sockfd, &n_seq, sizeof(n_seq), 0, (struct sockaddr *)&addr,
               addr_len);
        printf("RETRANSMITTED frame %d\n", i);
      }
    }
  }
  printf("Transmitted all frames\n");
  close(sockfd);

  return EXIT_SUCCESS;
}
