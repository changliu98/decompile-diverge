int func0(char *str) {
    int i, j, k, l, m, n, p, q;
    char buf[256];

    i = j = k = l = m = n = p = q = 0;
    while (1) {
        if (str[i] == 0)
            break;
        if (str[i] >= '0' && str[i] <= '9') {
            buf[j++] = str[i];
        } else {
            if (j) {
                buf[j] = 0;
                k = atoi(buf);
                if (k > l)
                    l = k;
                j = 0;
            }
        }
        i++;
    }
    if (j) {
        buf[j] = 0;
        k = atoi(buf);
        if (k > l)
            l = k;
    }
    return l;
}