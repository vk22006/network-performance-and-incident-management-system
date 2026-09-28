#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {

    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result != 0) {
        std::cout << "Initialization failed";
        WSACleanup();
        return 1;
    }

    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo* addressResults = nullptr;

    result = getaddrinfo(
        "cloudflare.com",
        "443",
        &hints,
        &addressResults
    );

    if (result != 0) {
        std::cout << "DNS resolution failed\n";

        WSACleanup();
        return 1;
    }

    std::cout << "DNS resolution successful\n";

    freeaddrinfo(addressResults);
    WSACleanup();
    return 0;
}