int write_sock(int fd, char *buf, int count) {
    int n = -1;
    n = write(fd, buf, count);
    if (n < 0) {
        perror("Error writing file");
        return -1;
    }
    return count - n;
}