int write_socket(int sock, char *buffer, int len) {
    int bytes_sent = 0;
    int ret;

    while (len > 0 && (ret = write(sock, buffer, len)) > 0) {
        bytes_sent += ret;
        buffer += ret;
        len -= ret;
    }

    return bytes_sent;
}