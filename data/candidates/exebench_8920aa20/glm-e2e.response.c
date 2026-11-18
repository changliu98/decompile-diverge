ssize_t medusaReceiveInternal(int fd, void *buf, size_t len) {
    return recv(fd, buf, len, 0);
}