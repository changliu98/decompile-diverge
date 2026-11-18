static char *ReadNumber(char *str, double *val) {
    char *end;
    double factor;
    int digit, point;

    factor = 1.0;
    for (;;) {
        switch (*str) {
        case '+':
        case '-':
            if (str == end)
                return NULL;
            factor = (*str == '-')? -1.0 : 1.0;
            break;
        case '\0':
            return NULL;
        default:
            for (point = 0, digit = 0;; ++str) {
                if (*str >= '0' && *str <= '9') {
                    digit = digit * 10 + (*str - '0');
                } else if (*str == '.') {
                    if (point)
                        return NULL;
                    point = 1;
                } else {
                    break;
                }
            }
            *val = factor * (digit + point * pow(10, -digit));
            end = str;
            return end;
        }
    }
}