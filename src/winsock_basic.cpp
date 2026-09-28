#include <iostream>
#include <WinSock2.h>

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

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}