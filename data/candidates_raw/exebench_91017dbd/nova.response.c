void func0(const char *path, int *mode) {
    if (access(path, F_OK)!= 0) {
        int err = errno;
        *mode = err;
        return;
    }

    struct stat buf;
    stat(path, &buf);
    *mode = buf.st_mode;
}