int func0(int *n, char *s) {
    int res;

    *n = 0;
    while (1) {
        if (*s == 0) {
            res = 0;
            break;
        }
        if (*s < '0' || *s > '9') {
            res = -1;
            break;
        }
        *n = *n * 10 + *s - '0';
        s++;
    }
    return res;
}