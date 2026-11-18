void Q_ParseNewlines(char *dest, char *src, int n) {
    char *p;
    char c;
    int i;

    p = dest;
    while (1) {
        if (*src!= '\0') {
            if (i > 1) {
                c = *src;
            } else {
                c = '\0';
            }
        } else {
            c = '\0';
        }

        if (c % 2 == 0) {
            if (*src == '\\' && *(src + 1) == 'n') {
                c = '\n';
                src++;
            }
        }

        *p = c;
        p++;
        src++;
        n--;

        if (n < 0) {
            break;
        }
    }

    *p = '\0';
}