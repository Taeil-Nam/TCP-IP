# TCP/IP Protocol Stack
This project implements a simplified TCP/IP protocol stack from scratch.  
It was developed for educational purposes and hands-on understanding of network protocol internals.

---

## 🚀 Goal
Implement the following network protocols:
- [ ] Ethernet (IEEE 802.3)
- [ ] ARP (Address Resolution Protocol)
- [ ] IP (Internet Protocol)
- [ ] ICMP (Internet Control Message Protocol)
- [ ] UDP (User Datagram Protocol)

---

## 🛠 Environment
- **CPU**: x86_64
- **OS**: Ubuntu 20.04
- **Kernel Version**: 5.15.0-136

---

## 🔍 Features
- Manual packet parsing and construction.
- Raw socket-based Ethernet frame handling.
- Independent protocol stack, not relying on Linux networking stack.

---

## 📚 References
- [RFC 894](https://datatracker.ietf.org/doc/html/rfc894) - Standard for the transmission of IP datagrams over Ethernet networks (Ethernet)
- [RFC 826](https://datatracker.ietf.org/doc/html/rfc826) - Address Resolution Protocol (ARP)
- [RFC 791](https://datatracker.ietf.org/doc/html/rfc791) - Internet Protocol (IP)
- [RFC 792](https://datatracker.ietf.org/doc/html/rfc792) - Internet Control Message Protocol (ICMP)
- [RFC 768](https://datatracker.ietf.org/doc/html/rfc768) - User Datagram Protocol (UDP)
