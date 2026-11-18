char *unmakemask(int mode, char *buf) {
    int i = 0;
    if (mode & 1)
        buf[i++] = 'c';
    if (mode & 2)
        buf[i++] = 'r';
    if (mode & 4)
        buf[i++] = 'l';
    buf[i] = '\0';
    return buf;
}