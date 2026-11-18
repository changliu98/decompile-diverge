int func0(char *s) {
    int len = strlen(s);
    if (len < 3)
        return 0;
    int i;
    char flag = 0;
    for (i = 2; i * i <= len; i++) {
        if (len % i == 0) {
            flag = 0;
            break;
        }
    }
    return flag & 1;
}