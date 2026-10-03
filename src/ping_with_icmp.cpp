#include <iostream>
#include <Windows.h>
#include <Iphlpapi.h>
#include <IcmpAPI.h>

#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")

int main() {
    HANDLE icmpHandle = IcmpCreateFile();

    if (icmpHandle == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create ICMP handle\n";
        return 1;
    }

    IPAddr destination = inet_addr("1.1.1.1");

    char data[] = "Hello";

    char replyBuffer[sizeof(ICMP_ECHO_REPLY) + 32];

    DWORD result = IcmpSendEcho(
        icmpHandle,
        destination,
        data,
        sizeof(data),
        nullptr,
        replyBuffer,
        sizeof(replyBuffer),
        1000
    );

    if (result == 0) {
        std::cout << "Ping failed\n";
    }
    else {
        ICMP_ECHO_REPLY* reply =
            reinterpret_cast<ICMP_ECHO_REPLY*>(replyBuffer);

        std::cout << "Ping successful\n";

        std::cout << "RTT: "
                  << reply->RoundTripTime
                  << " ms\n";
    }

    IcmpCloseHandle(icmpHandle);

    return 0;
}