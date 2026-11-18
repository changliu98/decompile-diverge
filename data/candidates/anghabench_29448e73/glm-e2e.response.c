int hex_to_int(const char *str, int *val) {
    *val = 0;
    for (int i = 0; i < 8; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            *val = (*val << 4) + str[i] - '0';
        } else if (str[i] >= 'a' && str[i] <= 'f') {
            *val = (*val << 4) + str[i] - 'a' + 10;
        } else {
            return 0;
        }
    }
    return 1;
}