char *func0(int mode, char *buf) {
    int i = 0;
    if (S_ISREG(mode))
        buf[i++] = '-';
    if (S_ISDIR(mode))
        buf[i++] = 'd';
    if (S_ISLNK(mode))
        buf[i++] = 'l';
    buf[i] = '\0';
    return buf;
}