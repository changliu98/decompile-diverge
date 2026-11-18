int func0(const char *str, int b) {
    char first[10];
    char second[10];
    int flag = 0;
    int idx = 0;
    int i = 0;

    memset(first, 0, 10);
    memset(second, 0, 10);

    while (str[i] != '\0') {
        if (isspace(str[i])) {
            if (flag == 0) {
                if (idx > 0) {
                    flag = 1;
                    idx = 0;
                }
            }
        } else {
            if (flag == 0) {
                first[idx++] = str[i];
            } else {
                second[idx++] = str[i];
            }
        }
        i++;
    }

    return b - atoi(first) - atoi(second);
}