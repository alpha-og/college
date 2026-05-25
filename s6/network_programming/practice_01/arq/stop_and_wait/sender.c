#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_FRAMES 10
int main() {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  memset(&addr, 0, addr_len);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(8085);

  struct timeval tv = {2, 0};
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

  char buffer[32];
  int seq = 0;
  int ack = -1;

  while (seq < TOTAL_FRAMES) {
    int n_seq = htonl(seq);
    sendto(sockfd, &n_seq, sizeof(n_seq), 0, (struct sockaddr *)&addr,
           addr_len);
    printf("TRANSMITTED packet %d\n", seq);
    if (recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&addr,
                 &addr_len) > 0) {
      ack = ntohl(ack);
      printf("RECEIVED ACK %d\n", ack);
      seq++;
    } else {
      printf("TIMEOUT... RETRANSMITTING\n");
    };
  }
  return EXIT_SUCCESS;
}
