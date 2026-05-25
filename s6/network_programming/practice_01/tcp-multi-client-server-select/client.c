#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define IP_ADDR "127.0.0.1"
#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_addr;
  socklen_t server_addr_len = sizeof(server_addr);
  memset(&server_addr, 0, server_addr_len);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  inet_pton(AF_INET, IP_ADDR, &server_addr.sin_addr);

  printf("[INFO] Connecting to %s:%d...\n", IP_ADDR, PORT);

  if (connect(client_socket, (struct sockaddr *)&server_addr, server_addr_len) <
      0) {
    perror("[ERROR] (connect)");
    exit(EXIT_FAILURE);
  }

  printf("[INFO] Connected to %s:%d\n", IP_ADDR, PORT);

  fd_set read_fds;
  char buffer[BUFFER_SIZE] = {0};
  int bytes_read = 0;

  printf("you>> ");
  fflush(stdout);

  while (1) {
    FD_ZERO(&read_fds);
    FD_SET(client_socket, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    int max_fd = client_socket;

    if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
      perror("[ERROR] (select)");
      exit(EXIT_FAILURE);
    }

    if (FD_ISSET(client_socket, &read_fds)) {
      memset(buffer, 0, BUFFER_SIZE);
      if ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) <= 0) {
        if (bytes_read < 0) {
          perror("[ERROR] (recv)");
          continue;
        } else {
          printf("\n[INFO] Server disconnected\n");
          exit(EXIT_SUCCESS);
        }
      }
      buffer[strcspn(buffer, "\n")] = '\0';
      printf("\n[BROADCAST] %s\n", buffer);
      printf("you>> ");
      fflush(stdout);
    }

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      memset(buffer, 0, BUFFER_SIZE);
      if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        continue;
      }
      if (send(client_socket, buffer, BUFFER_SIZE, 0) < 0) {
        perror("ERROR (send)");
      }

      printf("you>> ");
      fflush(stdout);
    }
  }
  return EXIT_SUCCESS;
}
