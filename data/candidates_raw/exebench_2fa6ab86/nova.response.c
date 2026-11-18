int func0(int sock, struct sockaddr *addr, socklen_t addrlen) {
    short port = 0;
    port = ntohs(addr->sa_family);
    return port;
}