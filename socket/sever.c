#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    unsigned short port;
    struct sockaddr_in Client_info;
    socklen_t Client_Info_Len = sizeof(Client_info);

    struct sockaddr_in Server_info;
    int Socket_Serv_FD, Socket_Client_FD;
    int result;

    char message[100];
    char Message_From_Client[100];

    port = 23232;

    printf("Server initiating connection ... \n");

    // Create socket
    Socket_Serv_FD = socket(AF_INET, SOCK_STREAM, 0);
    if (Socket_Serv_FD < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Binding information
    Server_info.sin_family = AF_INET;
    Server_info.sin_port = htons(port); // Convert port number to network byte order
    Server_info.sin_addr.s_addr = INADDR_ANY;

    // Bind with port to the socket
    result = bind(Socket_Serv_FD, (struct sockaddr *)&Server_info, sizeof(Server_info));
    if (result < 0) {
        perror("Binding socket failed");
        close(Socket_Serv_FD);
        return -1;
    }

    // Listen for connections on socket
    result = listen(Socket_Serv_FD, 1); 
    if (result < 0) {
        perror("Listen socket failed");
        close(Socket_Serv_FD);
        return -1;
    }

    // Accept when a connection occurs
    Socket_Client_FD = accept(Socket_Serv_FD, (struct sockaddr *)&Client_info, &Client_Info_Len);
    if (Socket_Client_FD < 0) {
        perror("Socket connection failed");
        close(Socket_Serv_FD);
        return -1;
    }

    while (1) {
        // Read message from client
        memset(Message_From_Client, 0, sizeof(Message_From_Client)); // Clear buffer
        result = read(Socket_Client_FD, Message_From_Client, sizeof(Message_From_Client) - 1);
        if (result < 0) {
            perror("Socket read failed");
            break;
        }

        printf("Message from client >> %s\n", Message_From_Client);

        // Prompt for message to send to client
        printf("Type a message to the client: ");
        if (fgets(message, sizeof(message), stdin) == NULL) {
            perror("fgets failed");
            break;
        }
        message[strcspn(message, "\n")] = '\0'; // Remove newline character

        // Send message to client
        result = write(Socket_Client_FD, message, strlen(message));
        if (result < 0) {
            perror("Message send failed");
            break;
        }
    }

    close(Socket_Serv_FD);
    close(Socket_Client_FD);
    return 0;
}
