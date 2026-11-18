int func0(char c, char *ret) {
    int i = 0;
    if (c >= '0' && c <= '9') {
        *ret = c - '0';
    } else if (c >= 'A' && c <= 'F') {
        *ret = c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        *ret = c - 'a' + 10;
    } else {
        i = -1;
    }
    return i;
}