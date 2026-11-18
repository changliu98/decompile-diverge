int write_data(int fd, void *buf, unsigned int count) {
    int written = 0;
    int ret;

    while (written != count) {
        ret = write(fd, buf + written, count - written);
        if (ret <= 0) {
            return -1;
        }
        written += ret;
    }
    
    return 0;
}