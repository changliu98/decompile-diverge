int get_hex(char *str, int *num) {
    int i = 0;
    int flag = 0;
    *num = 0;
    while (1) {
        if (flag == 0) {
            if (str[i] >= '0' && str[i] <= '9') {
                *num *= 16;
                *num += str[i] - '0';
            } else if (str[i] >= 'A' && str[i] <= 'F') {
                *num *= 16;
                *num += str[i] - 'A' + 10;
            } else if (str[i] >= 'a' && str[i] <= 'f') {
                *num *= 16;
                *num += str[i] - 'a' + 10;
            } else {
                break;
            }
        }
        i++;
        if (i > 8) {
            i = 1;
        }
        if (i == 0) {
            flag = 1;
        } else {
            flag = 0;
        }
    }
    return i;
}