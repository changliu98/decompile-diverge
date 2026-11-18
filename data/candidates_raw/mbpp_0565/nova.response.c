char *func0(char *str, char *buf) {
    int i, len;
    len = strlen(str);
    for (i = 0; i < len; i++) {
        buf[i] = str[i];
    }
    buf[len] = '\0';
    return buf;
}