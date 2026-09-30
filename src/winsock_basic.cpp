#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2,2), &wsaData); // Init. winsock
    // if WSAStartup() returns 0 - passed; else failed

    if(result != 0) {
        std::cout << "Initialization failed\n";
        return 0;
    }

    std::cout << "Initialization success\n";

    //Address = IPv6 (AF_INET6); Communication = TCP-style byte stream (SOCK_STREAM); Protocol = TCP (IPROTO_TCP)
    SOCKET clientSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

    if(clientSocket == INVALID_SOCKET) {
        std::cout << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    std::cout << "Socket created successfully\n";

    // Create and connect with server address
    sockaddr_in6 serverAddress{};

    serverAddress.sin6_family = AF_INET6;
    serverAddress.sin6_port = htons(443);   // 443 - HTTPS Port
    inet_pton(AF_INET6, "2606:4700::6810:85e5", &serverAddress.sin6_addr); // "2606:4700::6810:85e5" is IPv6 of cloudflare.com

    result = connect(
        clientSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),  // This parameter collects a common sockaddr pointer, so we reinterpret cast to sockaddr*
        sizeof(serverAddress)
    );

    if(result == SOCKET_ERROR) {
        std::cout << "Connection failed\n";
        std::cout << "Error code: " << WSAGetLastError() << '\n';

        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    
    std::cout << "Connected Successfully";

    // Clean up
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}