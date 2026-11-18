short recv_data(int fd, void *buf, unsigned short n) {
    short bytes_read;
    bytes_read = read(fd, buf, n);
    return bytes_read;
}