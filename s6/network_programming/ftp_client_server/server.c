#include <arpa/inet.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BACKLOG 5

#define CMD_PUT 1
#define CMD_GET 2
#define CMD_QUIT 3
#define CMD_UNDEFINED -1

#define BUFFER_SIZE 1024

#define FATAL 1

#define CHECK(cond, msg, is_fatal)                                             \
  do {                                                                         \
    if (cond) {                                                                \
      fprintf(stderr, "(system)>> %s:%d: %s: %s\n", __FILE__, __LINE__, msg,   \
              strerror(errno));                                                \
      if (is_fatal)                                                            \
        exit(EXIT_FAILURE);                                                    \
      else                                                                     \
        continue;                                                              \
    }                                                                          \
  } while (0);

int get_cmd(char *);

int main() {
  int port = 8080;

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  CHECK(sock_fd < 0, "Failed to create socket", FATAL);

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  CHECK(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0,
        "Failed to bind socket", FATAL);

  CHECK(listen(sock_fd, BACKLOG) < 0, "Unable to listen for connections",
        FATAL);
  fprintf(stdout, "(system)>> Server listening on port %d\n", port);

  struct sockaddr_in client_addr;
  socklen_t client_addr_size;
  int client_sock_fd;

  while (1) {
    client_addr_size = sizeof(client_addr);
    CHECK((client_sock_fd = accept(sock_fd, (struct sockaddr *)&client_addr,
                                   &client_addr_size)) < 0,
          "Failed to accept connection", !FATAL);
    char client_ip_address[INET_ADDRSTRLEN];
    int client_port = ntohs(client_addr.sin_port);
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip_address,
              INET_ADDRSTRLEN);
    fprintf(stdout, "(system)>> Client connected from %s:%d\n",
            client_ip_address, client_port);

    if (fork() == 0) {
      close(sock_fd);

      int bytes_received;
      int should_quit = 0;
      char cmd_buffer[BUFFER_SIZE] = {'\0'};
      char cmd_arg_buffer[BUFFER_SIZE] = {'\0'};
      char file_buffer[BUFFER_SIZE] = {'\0'};
      char file_path[BUFFER_SIZE];
      uint32_t filesize = 0;
      uint32_t filesize_net = 0;
      uint32_t remaining = 0;
      FILE *fptr = NULL;

      while (!should_quit) {
        CHECK((bytes_received = recv(client_sock_fd, cmd_buffer, BUFFER_SIZE,
                                     MSG_WAITALL)) <= 0,
              "Failed to receive bytes from client", !FATAL);
        cmd_buffer[bytes_received] = '\0';

        fprintf(stdout, "cmd: %s\n", cmd_buffer);

        switch (get_cmd(cmd_buffer)) {
        case CMD_PUT:
          CHECK((bytes_received = recv(client_sock_fd, cmd_arg_buffer,
                                       BUFFER_SIZE, MSG_WAITALL)) <= 0,
                "Failed to receive bytes from client", !FATAL);
          fprintf(stdout, "cmd_arg: %s\n", cmd_arg_buffer);
          cmd_arg_buffer[bytes_received] = '\0';
          CHECK(strlen(cmd_arg_buffer) == 0, "PUT requires a file name",
                !FATAL);

          CHECK((bytes_received = recv(client_sock_fd, &filesize_net,
                                       sizeof(filesize_net), 0)) <= 0,
                "Failed to receive bytes from client", !FATAL);
          filesize = ntohl(filesize_net);

          snprintf(file_path, sizeof(file_path), "%s/%s", "server_store",
                   cmd_arg_buffer);
          CHECK((fptr = fopen(file_path, "wb")) == NULL,
                "Unable to open file to write", FATAL);

          fprintf(stdout, "(system)>> Ingesting file to %s\n", file_path);

          remaining = filesize;

          while (remaining) {
            size_t pending =
                (size_t)(remaining < sizeof(file_buffer) ? remaining
                                                         : sizeof(file_buffer));
            CHECK((bytes_received =
                       recv(client_sock_fd, file_buffer, pending, 0)) <= 0,
                  "Failed to receive bytes from server (file maybe corrupt or "
                  "incomplete)",
                  FATAL);
            fwrite(file_buffer, 1, bytes_received, fptr);
            remaining -= bytes_received;
          }
          fclose(fptr);
          fprintf(stdout, "(system)>> File ingestion complete\n");
          break;
        case CMD_GET:
          CHECK((bytes_received = recv(client_sock_fd, cmd_arg_buffer,
                                       BUFFER_SIZE, MSG_WAITALL)) <= 0,
                "Failed to receive bytes from client", !FATAL);
          cmd_arg_buffer[bytes_received] = '\0';
          CHECK(strlen(cmd_arg_buffer) == 0, "GET requires a file name",
                !FATAL);
          snprintf(file_path, sizeof(file_path), "%s/%s", "server_store",
                   cmd_arg_buffer);

          uint32_t status = -1;
          if ((fptr = fopen(file_path, "rb")) == NULL) {
            status = htonl(404);
            CHECK(send(client_sock_fd, &status, sizeof(status), 0) < 0,
                  "Failed to send status", !FATAL);
            break;
          };
          status = htonl(200);
          CHECK(send(client_sock_fd, &status, sizeof(status), 0) < 0,
                "Failed to send status", !FATAL);

          fseek(fptr, 0, SEEK_END);
          filesize = htonl((uint32_t)(ftell(fptr)));
          rewind(fptr);

          CHECK(send(client_sock_fd, &filesize, sizeof(filesize), 0) < 0,
                "Failed to send filesize", !FATAL);

          size_t bytes_read;
          while ((bytes_read =
                      fread(file_buffer, 1, sizeof(file_buffer), fptr)) > 0) {
            send(client_sock_fd, file_buffer, bytes_read, 0);
          }
          fclose(fptr);
          fprintf(stdout, "(system)>> File sent successfully to %s:%d\n",
                  client_ip_address, client_port);
          break;

        case CMD_QUIT:
          fputs("(system)>> Quitting...\n", stdout);
          should_quit = 1;
          break;
        default:
          fputs("(system)>> Invalid command\n", stderr);
        }
      }
      close(client_sock_fd);
      exit(EXIT_SUCCESS);
    }
  }
  close(client_sock_fd);

  close(sock_fd);
  exit(EXIT_SUCCESS);
}

int get_cmd(char *cmd) {
  if (strcmp(cmd, "PUT") == 0)
    return CMD_PUT;
  else if (strcmp(cmd, "GET") == 0)
    return CMD_GET;
  else if (strcmp(cmd, "q") == 0)
    return CMD_QUIT;
  else
    return CMD_UNDEFINED;
}
