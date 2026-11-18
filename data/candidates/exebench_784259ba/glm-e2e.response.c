void inet_close(int *sock) {
    close(*sock);
    *sock = 0;
}