char * func0(char *str, int num) {
    int len = strlen(str);
    char *res = (char *)malloc((len + 1) * sizeof(char));
    int i = 0;
    while (1) {
        if (i >= len) break;
        res[i] = str[(i + num) % len];
        i++;
    }
    res[len] = '\0';
    return res;
}