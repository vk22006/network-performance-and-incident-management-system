#include <iostream>
#include <Windows.h>
#include <Iphlpapi.h>
#include <IcmpAPI.h>

#pragma comment(lib, "Iphlpapi.lib")

int main() {
    HANDLE icmpHandle = IcmpCreateFile();

    if (icmpHandle == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create ICMP handle\n";
        return 1;
    }

    std::cout << "ICMP handle created successfully\n";

    IcmpCloseHandle(icmpHandle);

    return 0;
}