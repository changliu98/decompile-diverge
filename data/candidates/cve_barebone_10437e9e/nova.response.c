unsigned short *bit_utf8_to_TU(char *s, int n) {
    unsigned long i = 0;
    unsigned long len = strlen(s);
    unsigned short *res;
    unsigned char c;
    unsigned char state;

    if (len > MAX_LEN) {
        error = 1;
        len = MAX_LEN;
    }
    res = (unsigned short *)calloc(2, len + 1);
    if (res == NULL) {
        error = 1;
        return NULL;
    }
    while (1) {
        while (len > 0 && (s[0] =='' || s[0] == '\n' || s[0] == '\t')) {
            s++;
            len--;
        }
        if (len == 0)
            break;
        if (s[0] == '\\') {
            if (len < 2)
                break;
            if (s[1] == 'r')
                c = '\r';
            else if (s[1] == 'n')
                c = '\n';
            else if (s[1] == 't')
                c = '\t';
            else
                c = s[1];
            s++;
            len--;
        } else {
            c = s[0];
        }
        res[i++] = c;
        s++;
        len--;
    }
    res[i] = 0;
    return res;
}