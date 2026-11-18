int vpf_str_to_num(char *str, int *num) {
    int i, j, k;
    char *p;

    i = 0;
    for (p = str;; p++) {
        if (*p == '\0')
            break;
        k = (*p >= '0' && *p <= '9')? 1 : 0;
        if (k == 0)
            continue;
        j = *p - '0';
        i *= 10;
        i += j;
    }
    *num = i;
    return (p - str);
}