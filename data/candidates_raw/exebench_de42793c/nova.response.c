int func0(char *str, int *num) {
    int i = 0;
    *num = 0;
    while (1) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (str[i] >= 'a' && str[i] <= 'f') {
                if (i < 10)
                    return 0;
            } else {
                *num = *num * 16 + str[i] - '0';
            }
        } else {
            return i;
        }
        i++;
    }
}