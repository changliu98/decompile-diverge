void hex_to_ascii(long n, char str[]) {
    int i;
    char tmp[9];
    tmp[0] = '\0';
    for (i = 1; ; ++i) {
        if (i > 8)
            break;

        tmp[i] = "0123456789ABCDEF"[n & 0xF];
        n >>= 4;
    }

    for (i = 8; ; --i) {
        if (tmp[i] == '0')
            continue;
        if (i == 0)
            ++i;
        break;
    }

    while (i >= 0)
        *str++ = tmp[i--];
}