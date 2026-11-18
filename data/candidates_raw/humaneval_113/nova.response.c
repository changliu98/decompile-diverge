char **func0(char **str, int strSize) {
    char **res = (char **)malloc(sizeof(char *) * strSize);
    for (int i = 0; i < strSize; i++) {
        int start = 0, end = 0;
        while (1) {
            if (str[i][end] == '\0') {
                res[i] = (char *)malloc(sizeof(char) * 100);
                sprintf(res[i], "%d->%d", start, end);
                break;
            }
            if (str[i][end]!= '0' && str[i][end] >= '0' && str[i][end] <= '9' &&
                (str[i][end] - '0') % 2 == 1) {
                start = end + 1;
            } else {
                end++;
            }
        }
    }
    return res;
}