#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BACKLOG 5
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

  // initialize default configuration
  int concurrent_clients = 1;
  int port = 8080;

  // parse cli args
  int opt;
  while ((opt = getopt(argc, argv, "p:c:")) != -1) {
    switch (opt) {
    case 'p':
      port = atoi(optarg);
      break;
    case 'c':
      concurrent_clients = atoi(optarg);
      break;
    default:
      fprintf(stderr,
              "Usage: %s [-p port] [-c no of allowed concurrent clients]\n",
              argv[0]);
      return EXIT_FAILURE;
      break;
    }
  }

  // validate configuration
  if (port < 0 || port > (1 << 16) - 1) {
    fprintf(stderr, "Error: Port must be in the range of 0 to 65535.\n");
    return EXIT_FAILURE;
  }

  if (port > 0 && port < 1 << 10) {
    fprintf(stderr,
            "Error: Ports below 1024 are privileged. Use 0 or 1024-65535.\n");
    return EXIT_FAILURE;
  }

  if (concurrent_clients < 1) {
    fprintf(stderr,
            "Error: Number of allowed concurrent clients must be positive.\n");
    return EXIT_FAILURE;
  }

  // create socket
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  // initialize socket data structures
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // bind socket to ip and port
  if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Error: Failed to bind socket.\n");
    return EXIT_FAILURE;
  }
  printf("Successfully bound socket.\n");

  // listen for incoming connection requests on bound socket
  if (listen(sock_fd, BACKLOG) < 0) {
    perror("Error: Unable to listen for connections.\n");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "Server listening on port %d...\n", port);

  struct sockaddr_storage client_addr;
  socklen_t addr_size = sizeof(client_addr);
  int client_sock_fd;

  while (1) {
    // accept client connection requests by consuming requests from the accept
    // buffer
    if ((client_sock_fd = accept(sock_fd, (struct sockaddr *)&client_addr,
                                 &addr_size)) < 0) {
      perror("Error: Unable to accept connection.\n");
      return EXIT_FAILURE;
    }

    /* fprintf(stdout, "Client %s connected.\n", inet_ntop(client_addr)); */

    if (fork() == 0) {
      close(sock_fd);

      // receive data from client
      ssize_t bytes_received;
      char buffer[BUFFER_SIZE];

      int should_quit = 0;
      char response[BUFFER_SIZE];

      while (!should_quit) {
        if ((bytes_received =
                 recv(client_sock_fd, buffer, BUFFER_SIZE - 1, 0)) < 0) {
          perror("Error: Unable to receive bytes from client.\n");
          return EXIT_FAILURE;
        }
        buffer[bytes_received] = '\0';
        fprintf(stdout, "Received: %s\n", buffer);
        if (strcmp(buffer, "\\q") == 0) {
          fprintf(stdout, "Exiting...\n");
          should_quit = 1;
        }

        snprintf(response, sizeof(response),
                 "Successfully received your message \"%s\"", buffer);
        send(client_sock_fd, response, strlen(response), 0);
      }

      close(client_sock_fd);
      return EXIT_SUCCESS;
    }
  }
  close(sock_fd);
  return EXIT_SUCCESS;
}
