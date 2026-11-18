int str_to_int(char *str, int *num) {
    int i = 0, j = 10, k;
    *num = 0;
    j = 10;
    if (str[i] == '0' && str[i + 1] == 'x') {
        i = 2;
        j = 16;
    }
    if (str[i] == '\0')
        k = -1;
    else {
        while (str[i]!= '\0') {
            if (j == 16) {
                if (str[i] >= 'A' && str[i] <= 'F')
                    k = str[i] - 'A' + 10;
            } else {
                if (j == 16) {
                    if (str[i] >= 'a' && str[i] <= 'f')
                        k = str[i] - 'a' + 10;
                } else
                    k = str[i] - '0';
            }
            *num = *num * j + k;
            i++;
        }
        k = 0;
    }
    return k;
}