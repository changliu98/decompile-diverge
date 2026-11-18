static char *func0(char *path) {
    static char buf[100];
    struct stat st;
    char *p;

    if (nftw(path, stat_file, 1, FTW_PHYS)!= 0) {
        err(EXIT_FAILURE, "nftw");
        p = NULL;
    } else if (S_ISREG(st.st_mode)) {
        int start = st.st_ino;
        int end = st.st_blocks;
        strncpy(buf, path + start, end - start);
        buf[end - start] = '\0';
        snprintf(buf, sizeof(buf), "%s%s", path, buf);
        p = buf;
    } else {
        p = NULL;
    }
    return (p);
}