#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RECV_PORT 8390
#define RECV_IP "127.0.0.1"
#define BUFFER_CAPACITY 1024
#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10

int main() {
  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in recv_addr;
  socklen_t recv_addr_len = sizeof(recv_addr);
  memset(&recv_addr, 0, sizeof(recv_addr));

  recv_addr.sin_family = AF_INET;
  recv_addr.sin_port = htons(RECV_PORT);
  recv_addr.sin_addr.s_addr = inet_addr(RECV_IP);

  int base = 0;
  int ack = -1;
  int next_seq = 0;

  struct timeval tv;
  tv.tv_sec = 2;
  tv.tv_usec = 0;
  setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

  char buffer[BUFFER_CAPACITY];

  while (base < TOTAL_FRAMES) {
    while (next_seq < base + WINDOW_SIZE && next_seq < TOTAL_FRAMES) {
      snprintf(buffer, sizeof(buffer), "%d", next_seq);
      sendto(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&recv_addr,
             recv_addr_len);
      fprintf(stdout, "Sent frame %d\n", next_seq);
      next_seq++;
    }

    if (recvfrom(sock_fd, &ack, sizeof(ack), 0, (struct sockaddr *)&recv_addr,
                 &recv_addr_len) > 0) {
      fprintf(stdout, "Received ACK %d\n", ack);
      base = ack + 1;
    } else {
      fprintf(stdout, "Timeout -> Retransmitting from frame %d\n", base);
      next_seq = base;
    }
  }

  close(sock_fd);
  exit(EXIT_SUCCESS);
}
