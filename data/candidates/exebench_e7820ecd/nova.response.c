int read_all(int sock, char *buf, int len) {
    int time_recv, check;
    char *ptmp = buf;

    do {
        if ((time_recv = recv(sock, ptmp, len, 0)) <= 0) {
            return 0;
        }

        len -= time_recv;
        ptmp += time_recv;
    } while (len > 0);

    return time_recv;
}