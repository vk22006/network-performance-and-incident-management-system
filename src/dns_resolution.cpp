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

    // Displaying DNS info using linked-list traversal
    for (addrinfo* current = addressResults;
        current != nullptr;
        current = current->ai_next) {

        char addressBuffer[INET6_ADDRSTRLEN];

        if (current->ai_family == AF_INET)
        {
            std::cout << "IPv4 address found\n";

            sockaddr_in* address =
                reinterpret_cast<sockaddr_in*>(current->ai_addr);

            inet_ntop(
                AF_INET,
                &address->sin_addr,
                addressBuffer,
                sizeof(addressBuffer)
            );
        }
        else if (current->ai_family == AF_INET6)
        {
            std::cout << "IPv6 address found\n";

            sockaddr_in6* address =
                reinterpret_cast<sockaddr_in6*>(current->ai_addr);

            inet_ntop(
                AF_INET6,
                &address->sin6_addr,
                addressBuffer,
                sizeof(addressBuffer)
            );
        }

        std::cout << "Socket type: "
                << current->ai_socktype << '\n';

        std::cout << "Protocol: "
                << current->ai_protocol << '\n';

        std::cout << "Address: " << addressBuffer << '\n';

        std::cout << '\n';
    }

    freeaddrinfo(addressResults);
    WSACleanup();
    return 0;
}