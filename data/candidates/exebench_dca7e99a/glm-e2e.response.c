int _socket_close_(int *sock) {
    int fd = *sock;
    *sock = -1;
    int ret = close(fd);
    return ret;
}