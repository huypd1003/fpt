#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    struct sockaddr_in Server_info;
    int Socket_FD;
    int result;
    
    char message[100];
    char Message_From_Server[100];
    
    int port = 23232;
    
    printf("Initiating connection ...\n");
    
    // Create socket
    Socket_FD = socket(AF_INET, SOCK_STREAM, 0);
    if (Socket_FD == -1) {
        perror("Socket creation failed");
        return -1;
    }
    
    // Bind information
    Server_info.sin_family = AF_INET;
    Server_info.sin_port = htons(port); // Convert port number to network byte order

    
    // Connect to server
    result = connect(Socket_FD, (struct sockaddr *)&Server_info, sizeof(Server_info));
    if (result < 0) {
        perror("Connect socket failed");
        close(Socket_FD);
        return -1;
    }
    
    while (1) {
        // Get input message from user
        printf("Type a message to server or 'end' to close connection: ");
        if (fgets(message, sizeof(message), stdin) == NULL) {
            perror("fgets failed");
            break;
        }
        message[strcspn(message, "\n")] = '\0'; // Remove newline character
        
        // Send message to server
        result = write(Socket_FD, message, strlen(message));
        if (result < 0) {
            perror("Message send failed");
            break;
        }
        

        // Receive message from server
        memset(Message_From_Server, 0, sizeof(Message_From_Server)); // Clear buffer
        result = read(Socket_FD, Message_From_Server, sizeof(Message_From_Server) - 1);
        if (result < 0) {
            perror("Message receive failed");
            break;
        }
        
        Message_From_Server[result] = '\0'; // Null-terminate the received data
        printf("Message from server >> %s\n", Message_From_Server);
    }
    
    close(Socket_FD);
    return 0;
}
