int connectToServer(int *sock, char *ip, int port) {
    struct sockaddr_in addr;
    int ret;

    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if (*sock == -1) {
        ret = -1;
        goto err;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(*sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(*sock);
        ret = -1;
        goto err;
    }

    ret = 0;

err:
    return ret;
}