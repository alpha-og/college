#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RECV_PORT 8390
#define BUFFER_CAPACITY 1024
#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10

int main() {
  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in recv_addr, sndr_addr;
  socklen_t recv_addr_len = sizeof(recv_addr);
  socklen_t sndr_addr_len = sizeof(sndr_addr);
  memset(&recv_addr, 0, sizeof(recv_addr));
  memset(&sndr_addr, 0, sizeof(sndr_addr));

  recv_addr.sin_family = AF_INET;
  recv_addr.sin_port = htons(RECV_PORT);
  recv_addr.sin_addr.s_addr = INADDR_ANY;

  int expected = 0;
  int frame = -1;

  char buffer[BUFFER_CAPACITY];

  bind(sock_fd, (struct sockaddr *)&recv_addr, recv_addr_len);

  while (1) {
    recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&sndr_addr,
             &sndr_addr_len);
    frame = atoi(buffer);
    fprintf(stdout, "Received frame %d\n", frame);
    if (frame == expected && rand() % 2 == 1) {
      fprintf(stdout, "Accepted frame %d\n", frame);
      sendto(sock_fd, &frame, sizeof(frame), 0, (struct sockaddr *)&sndr_addr,
             sndr_addr_len);
      expected++;
    } else {

      fprintf(stdout, "Sending NACK %d\n", frame);
      int nack = expected - 1;
      sendto(sock_fd, &nack, sizeof(nack), 0, (struct sockaddr *)&sndr_addr,
             sndr_addr_len);
    }
  }

  close(sock_fd);
  exit(EXIT_SUCCESS);
}
