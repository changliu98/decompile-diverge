int sendcw(int fd, const void *buf) {
    if (send(fd, buf, 18, 0) == -1) {
        syslog(LOG_ERR, "send failed: %m");
        return 0;
    }
    return 1;
}