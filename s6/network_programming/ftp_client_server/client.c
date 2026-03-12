#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CMD_HELP 0
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
  } while (0)

int get_cmd(char *);

int main() {
  int port = 8080;
  char ip_addr[INET_ADDRSTRLEN] = "127.0.0.1";

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  CHECK(sock_fd < 0, "Failed to create socket", FATAL);

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  CHECK(inet_pton(AF_INET, ip_addr, &server_addr.sin_addr.s_addr) != 1,
        "Failed to set server address", FATAL);

  CHECK(connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
            0,
        "Failed to connect to server", FATAL);

  int should_quit = 0;

  ssize_t bytes_received;
  char buffer[BUFFER_SIZE];
  char *cmd;
  char *cmd_arg;

  FILE *fptr;

  while (!should_quit) {
    memset(buffer, 0, sizeof(buffer));

    // read input
    fputs("(you)>> ", stdout);
    if (fgets(buffer, sizeof(buffer) - 1, stdin) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      cmd = strtok(buffer, " ");
      cmd_arg = strtok(NULL, " ");
      CHECK(cmd == NULL, "Failed to parse empty command", !FATAL);

      switch (get_cmd(cmd)) {
      case CMD_HELP:
        fputs("(system)>> Available commands:\n1.GET <filename>\n2. PUT "
              "<filename>\n3. q\n4. ?\n",
              stdout);
        break;
      case CMD_PUT:
        CHECK(cmd_arg == NULL, "PUT requires a file name", !FATAL);
        CHECK((fptr = fopen(cmd_arg, "rb")) == NULL, "Failed to open file",
              !FATAL);

        fprintf(stdout, "(system)>> Sending file %s\n", cmd_arg);

        send(sock_fd, cmd, strlen(cmd) + 1, 0); // send command to server
        send(sock_fd, cmd_arg, strlen(cmd_arg) + 1,
             0); // send filename to server

        // determine filesize
        fseek(fptr, 0, SEEK_END);
        long filesize;
        CHECK((filesize = ftell(fptr)) < 0, "Failed to determine file size",
              !FATAL);

        uint32_t filesize_net =
            htonl((uint32_t)filesize); // also convert to network long
        rewind(fptr);

        send(sock_fd, &filesize_net, sizeof(filesize_net),
             0); // send filesize to server

        // send file contents in chunks of 1024 bytes
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), fptr)) > 0) {
          send(sock_fd, buffer, bytes_read, 0);
        }
        fclose(fptr);
        fputs("(system)>> File upload complete\n", stdout);
        break;
      case CMD_GET:
        CHECK(cmd_arg == NULL, "GET requires a file name", !FATAL);

        fprintf(stdout, "(system)>> Fetching file %s\n", cmd_arg);
        send(sock_fd, cmd, strlen(cmd) + 1, 0); // send command to server
        send(sock_fd, cmd_arg, strlen(cmd_arg) + 1,
             0); // send filename to server

        // receive response status
        uint32_t status_net;
        CHECK((bytes_received =
                   recv(sock_fd, &status_net, sizeof(status_net), 0)) <= 0,
              "Failed to receive bytes from server", !FATAL);
        int status = ntohl(status_net);
        if (status == 404) {
          fprintf(stdout,
                  "(system)>> Failed to fetch file from server: File not "
                  "found: %s\n",
                  cmd_arg);
        } else if (status == 200) {
          // receive filesize
          uint32_t filesize_net;
          CHECK((bytes_received = recv(sock_fd, &filesize_net,
                                       sizeof(filesize_net), 0)) <= 0,
                "Failed to receive bytes from server", !FATAL);
          uint32_t filesize = ntohl(filesize_net);

          CHECK((fptr = fopen(cmd_arg, "wb")) == NULL,
                "Failed to open file to write contents", !FATAL);

          fprintf(stdout, "(system)>> Downloading to %s\n", cmd_arg);
          uint32_t remaining = filesize;
          while (remaining) {
            size_t pending =
                (size_t)(remaining < sizeof(buffer) ? remaining
                                                    : sizeof(buffer));
            CHECK((bytes_received = recv(sock_fd, buffer, pending, 0)) <= 0,
                  "Failed to receive bytes from server (received file maybe "
                  "corrupt or incomplete)",
                  !FATAL);
            fwrite(buffer, 1, bytes_received, fptr);
            remaining -= bytes_received;
          }
          fclose(fptr);
          fputs("(system)>> File download complete\n", stdout);
        }
        break;
      case CMD_QUIT:
        fputs("(system)>> Quitting...\n", stdout);
        should_quit = 1;
        break;
      default:
        fputs("(system)>> Invalid command\n", stdout);
      }
    }
  }

  close(sock_fd);
  exit(EXIT_SUCCESS);
}

int get_cmd(char *cmd) {
  if (strcmp(cmd, "?") == 0)
    return CMD_HELP;
  else if (strcmp(cmd, "PUT") == 0)
    return CMD_PUT;
  else if (strcmp(cmd, "GET") == 0)
    return CMD_GET;
  else if (strcmp(cmd, "q") == 0)
    return CMD_QUIT;
  else
    return CMD_UNDEFINED;
}
