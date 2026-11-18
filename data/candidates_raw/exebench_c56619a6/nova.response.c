static int func0(int fd, char *name, size_t namesz, unsigned short *port) {
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    int rc;

    if (getsockname(fd, (struct sockaddr *)&sin, &len) == -1) {
        if (port)
            *port = 0;
        strcpy(name, "?");
        rc = -1;
    } else if (sin.sin_family == AF_INET) {
        struct sockaddr_in *sin4 = &sin;
        if (name)
            inet_ntop(AF_INET, &sin4->sin_addr, name, namesz);
        if (port)
            *port = ntohs(sin4->sin_port);
        rc = 0;
    } else {
        struct sockaddr_in6 *sin6 = &sin;
        if (name)
            inet_ntop(AF_INET6, &sin6->sin6_addr, name, namesz);
        if (port)
            *port = ntohs(sin6->sin6_port);
        rc = 0;
    }
    return rc;
}