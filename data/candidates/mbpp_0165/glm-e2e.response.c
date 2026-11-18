int func0(const char *str) {
    int count = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] - 'A' == i || str[i] - 'a' == i) {
            count++;
        }
    }
    return count;
}