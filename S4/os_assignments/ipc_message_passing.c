#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 256  // Define the size of the message
#define QUEUE_KEY 1234  // Define the key for the message queue

// Structure for message format
struct msg_buffer {
    long msg_type;        // Type of the message (must be > 0)
    char msg_text[MSG_SIZE]; // Message text
};

// Function to reverse the string
void reverse_string(char* str) {
    int len = strlen(str);
    int start = 0;
    int end = len - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() {
    struct msg_buffer message;
    int msgid;
    pid_t pid;

    // Create the message queue
    msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Create a child process using fork
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process (Sender)
        while (1) {
            printf("Enter message (type 'exit' to quit): ");
            fgets(message.msg_text, MSG_SIZE, stdin);
            message.msg_text[strcspn(message.msg_text, "\n")] = '\0';  // Remove newline character

            // Send the message to the receiver (message type 1)
            message.msg_type = 1;
            if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
                perror("msgsnd failed");
                exit(1);
            }

            // If the message is 'exit', break the loop
            if (strcmp(message.msg_text, "exit") == 0) {
                break;
            }

            // Receive the reversed message from the receiver (message type 2)
            if (msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0) == -1) {
                perror("msgrcv failed");
                exit(1);
            }

            printf("Reversed Message: %s\n", message.msg_text);
        }
    } else {  // Child process (Receiver)
        while (1) {
            // Receive the message from the sender (message type 1)
            if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
                perror("msgrcv failed");
                exit(1);
            }

            // If the message is 'exit', break the loop
            if (strcmp(message.msg_text, "exit") == 0) {
                break;
            }

            // Reverse the message
            reverse_string(message.msg_text);

            // Change the message type to 2 for sending the reversed message back
            message.msg_type = 2;

            // Send the reversed message back to the sender
            if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
                perror("msgsnd failed");
                exit(1);
            }
        }
    }

    // Delete the message queue (after both sender and receiver have finished)
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
