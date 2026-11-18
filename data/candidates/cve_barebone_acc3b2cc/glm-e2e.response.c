int sock_initaddress(const char *host, const char *port, struct addrinfo *hints, struct addrinfo **addr, char *errbuf, int errbuf_size) {
    int ret;
    int gai_err;
    const char *actual_port;

    if (port == NULL) {
        actual_port = "0"; // String located at 0x2034
    } else {
        actual_port = port;
    }

    gai_err = getaddrinfo(host, actual_port, hints, addr);

    if (gai_err != 0) {
        if (errbuf != NULL) {
            if (host != NULL && port != NULL) {
                // Try resolving with just the port to see if the host was the issue
                gai_err = getaddrinfo(NULL, actual_port, hints, addr);
                if (gai_err == 0) {
                    freeaddrinfo(*addr);
                    get_gai_errstring(errbuf, errbuf_size, gai_err, port, host, "%s"); // fmt at 0x20ec
                } else {
                    get_gai_errstring(errbuf, errbuf_size, gai_err, host, NULL, "%s"); // fmt at 0x20ec
                }
            } else {
                get_gai_errstring(errbuf, errbuf_size, gai_err, host, port, "%s"); // fmt at 0x20ec
            }
        }
        return -1;
    }

    // Check if the resolved family is AF_INET (2) or AF_INET6 (10)
    if ((*addr)->ai_family != 2 && (*addr)->ai_family != 10) {
        if (errbuf != NULL) {
            snprintf(errbuf, errbuf_size, "Neither IPv4 nor IPv6 address found"); // String at 0x2036
        }
        freeaddrinfo(*addr);
        *addr = NULL;
        return -1;
    }

    // Check if the socket type is SOCK_STREAM (1) and if it's a multicast address
    if ((*addr)->ai_socktype == 1 && sock_ismcastaddr((*addr)->ai_addr) != 0) {
        if (errbuf != NULL) {
            snprintf(errbuf, errbuf_size, "Multicast address cannot be used for TCP connections"); // String at 0x205f
        }
        freeaddrinfo(*addr);
        *addr = NULL;
        return -1;
    }

    return 0;
}