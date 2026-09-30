#include <iostream>
#include <chrono>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0) {
        std::cout << "Initialization failed\n";
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

    std::cout << "DNS resolution successful\n\n";

    SOCKET connectedSocket = INVALID_SOCKET;

    for (addrinfo* current = addressResults;
        current != nullptr;
        current = current->ai_next) {

        char addressBuffer[INET6_ADDRSTRLEN];

        if (current->ai_family == AF_INET) {
            sockaddr_in* address =
                reinterpret_cast<sockaddr_in*>(current->ai_addr);

            inet_ntop(
                AF_INET,
                &address->sin_addr,
                addressBuffer,
                sizeof(addressBuffer)
            );

            std::cout << "Trying IPv4: "
                    << addressBuffer << '\n';
        }
        else if (current->ai_family == AF_INET6) {
            sockaddr_in6* address =
                reinterpret_cast<sockaddr_in6*>(current->ai_addr);

            inet_ntop(
                AF_INET6,
                &address->sin6_addr,
                addressBuffer,
                sizeof(addressBuffer)
            );

            std::cout << "Trying IPv6: "
                    << addressBuffer << '\n';
        }

        SOCKET clientSocket = socket(
            current->ai_family,
            current->ai_socktype,
            current->ai_protocol
        );

        if (clientSocket == INVALID_SOCKET) {
            std::cout << "Socket creation failed\n\n";
            continue;
        }

        // Setting timer to calculate connect() duration
        auto start = std::chrono::steady_clock::now();

        result = connect(
            clientSocket,
            current->ai_addr,
            static_cast<int>(current->ai_addrlen)
        );

        auto end = std::chrono::steady_clock::now();

        auto connectTime =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start
            ).count();

        if (result == SOCKET_ERROR) {
            std::cout << "Connection failed\n\n";

            closesocket(clientSocket);
            continue;
        }

        std::cout << "Connection successful\n\n";
        std::cout << "TCP Connect Time: " << connectTime << "ms\n\n";

        connectedSocket = clientSocket;
        break;
    }

    freeaddrinfo(addressResults);

    if (connectedSocket != INVALID_SOCKET) {
        std::cout << "TCP connection established\n";

        closesocket(connectedSocket);
    }
    else {
        std::cout << "Could not connect to any address\n";
    }

    WSACleanup();

    return 0;
}