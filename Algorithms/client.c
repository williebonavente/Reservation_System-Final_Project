#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

// Function to handle communication with the server
void communicateWithServer(SOCKET serverSocket)
{
    char message[MAX_BUFFER_SIZE];
    int bytesRead, bytesSent;

    printf("Enter a message to send to the server (or type 'exit' to quit):\n");

    while (1)
    {
        // Read input from the user
        fgets(message, MAX_BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove trailing newline character

        // Send the message to the server
        bytesSent = send(serverSocket, message, strlen(message), 0);
        if (bytesSent == SOCKET_ERROR)
        {
            perror("Error sending message to server");
            break;
        }

        if (strcmp(message, "exit") == 0)
        {
            printf("Exiting the program.\n");
            break;
        }

        // Receive the response from the server
        bytesRead = recv(serverSocket, message, MAX_BUFFER_SIZE, 0);
        if (bytesRead == SOCKET_ERROR)
        {
            perror("Error receiving response from server");
            break;
        }

        if (bytesRead == 0)
        {
            printf("Connection closed by the server.\n");
            break;
        }

        // Null-terminate the received message
        message[bytesRead] = '\0';

        // Print the response from the server
        printf("Server response: %s\n", message);
    }
}

int main()
{
    WSADATA wsaData;
    SOCKET serverSocket;
    struct sockaddr_in serverAddress;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        perror("Failed to initialize Winsock");
        exit(1);
    }

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        perror("Error creating socket");
        WSACleanup();
        exit(1);
    }

    // Set up the server address structure
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    if (inet_ntoa(serverAddress.sin_addr) == NULL)
    {
        perror("Invalid server IP address");
        closesocket(serverSocket);
        WSACleanup();
        exit(1);
    }

    // Connect to the server
    if (connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        perror("Error connecting to the server");
        closesocket(serverSocket);
        WSACleanup();
        exit(1);
    }

    // Communicate with the server
    communicateWithServer(serverSocket);

    // Close the socket and clean up Winsock
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
