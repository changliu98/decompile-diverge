char *parse_content_length(char *s, char *e, int *ret) {
    char *p;
    int n;
    bool neg;

    for (p = s; p!= e; p++) {
        if (*p =='' || *p == '\t' || *p == '\n' || *p == '\r')
            continue;
        if (*p == '\n' || *p == '\r')
            break;
        neg = (*p == '-');
        if (neg)
            p++;
        for (; p!= e; p++) {
            if (*p =='' || *p == '\t')
                break;
            if (*p == '\n' || *p == '\r')
                break;
            n = (*p - '0');
            if (n < 0 || n > 9)
                break;
            if (neg)
                n = 0 - n;
            *ret = *ret * 10 + n;
        }
        break;
    }

    return p;
}