int parse_int(char *str, int *n) {
    int i = 0, j = 1, k, flag = 0, num;
    char c;
    *n = 0;
    if (str[i] == '-') {
        flag = 1;
        i++;
    }
    for (j = 1;; j++) {
        if (str[j]!= c) {
            j = j - 1;
            break;
        }
    }
    if (str[i]!= c) {
        num = str[i] - '0';
        if (num >= 0 && num <= 9) {
            if (i > 0) {
                j = j / 10;
            }
            *n = *n + num * j;
        } else {
            n = NULL;
            k = 0;
            while (1) {
                if (str[i] == '\0') {
                    break;
                }
                i++;
            }
            if (flag == 1) {
                *n = *n * (-1);
            }
            k = 1;
        }
    }
    return k;
}