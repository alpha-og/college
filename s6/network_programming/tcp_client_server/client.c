#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  char ip_address[INET_ADDRSTRLEN] = "127.0.0.1";
  int port = 8080;
  int opt;
  while ((opt = getopt(argc, argv, "a:p:")) != -1) {
    switch (opt) {
    case 'a':
      strcpy(ip_address, optarg);
      break;
    case 'p':
      port = atoi(optarg);
      break;
    default:
      fputs("Usage: %s [-a IP address] [-p port]\n", stderr);
      return EXIT_FAILURE;
    }
  }

  int sock_fd;
  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Error: Socket creation failed.\n");
  };

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0) {
    perror("Error: inet_pton");
    return EXIT_FAILURE;
  }

  if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("Error: Unable to connect to server.\n");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "Connected to %s:%d\n", ip_address, port);

  int should_quit = 0;
  char buffer[BUFFER_SIZE];
  ssize_t bytes_received;

  while (!should_quit) {
    // transmit message
    memset(buffer, 0, sizeof(buffer));
    fprintf(stdout, "(you) >> ");
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      if (strcmp(buffer, "\\q") == 0) {
        fprintf(stdout, "Exiting...\n");
        should_quit = 1;
      }
      send(sock_fd, buffer, strlen(buffer), 0);
    }

    // receive message
    memset(buffer, 0, sizeof(buffer));
    if ((bytes_received = recv(sock_fd, buffer, BUFFER_SIZE - 1, 0)) < 0) {
      perror("Error: Unable to receive data from the server.\n");
      return EXIT_FAILURE;
    }
    buffer[bytes_received] = '\0';
    fprintf(stdout, "(server) >> %s\n", buffer);
  }
  return EXIT_SUCCESS;
}
