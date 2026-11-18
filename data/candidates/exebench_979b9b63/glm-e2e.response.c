int openI2CBus(int *fd, const char *path) {
    *fd = open(path, O_RDWR);
    if (*fd < 0) {
        return 1;
    }
    return 0;
}