# Network Performance Monitoring and Incident Management Platform

A network monitoring agent that measures network performance metrics and integrates them with Salesforce for telemetry, automation, and analytics.

## Current Progress

**UNDER DEVELOPMENT**

The project currently focuses on **Windows socket programming and TCP connectivity**.

Implemented:

* WinSock initialization and cleanup
* TCP socket creation
* IPv4 and IPv6 support
* DNS/hostname resolution using `getaddrinfo()`
* Multiple-address handling
* TCP connection establishment with `connect()`
* Connection failure handling and fallback
* Basic network diagnostics

## Planned Architecture

```text
C++ Monitoring Agent
        │
        ├── DNS Resolution
        ├── TCP Connect Time
        ├── Latency
        ├── Packet Loss
        └── Network Statistics
                │
                ▼
          JSON / HTTPS
                │
                ▼
        Salesforce REST API
                │
                ▼
       Network Metric Records
                │
        ┌───────┴────────┐
        ▼                ▼
      Flows          Dashboards
```

## Tech Stack

* **C++20**
* **CMake**
* **WinSock2**
* **Windows Networking APIs**
* **libcurl** *(planned)*
* **nlohmann/json** *(planned)*
* **Salesforce Apex REST** *(planned)*

## Learning Approach

The project is being developed incrementally:

**Concept → Tiny Experiment → C++ Implementation → Project Feature**

This keeps the networking concepts understandable instead of turning the project into another magnificent pile of APIs nobody remembers six months later.

## Roadmap

* [x] Networking fundamentals
* [x] WinSock initialization
* [x] TCP socket creation
* [x] DNS resolution
* [x] IPv4/IPv6 address handling
* [x] TCP connection establishment
* [ ] TCP connection-time measurement
* [ ] Network latency measurement
* [ ] Packet-loss measurement
* [ ] Continuous monitoring
* [ ] JSON telemetry
* [ ] Salesforce REST integration
* [ ] Salesforce automation and dashboards
* [ ] Authentication
* [ ] Production-ready packaging

## License

This project uses GNU GPL3.0 license. For more details, refer [LICENSE](LICENSE)
