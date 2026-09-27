#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib");

int main() {
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2,2), &wsaData); // Init. winsock
    // if WSAStartup() returns 0 - passed; else failed

    if(result != 0) {
        std::cout << "Initialization failed\n";
        return 0;
    }

    std::cout << "Initialization success\n";

    return 0;
}