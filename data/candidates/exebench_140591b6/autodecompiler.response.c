void Q_ParseNewlines(char *s, char *t, int size) {
    int c;
    while (1) {
        if ((c = (*t == '\0' ? 0 : (size > 1 ? 1 : 0))) & 1) {
            if (*t == '\\' && *(t + 1) == 'n') {
                c = '\n';
                t++;
            } else {
                c = *t;
            }
            *s++ = c;
            t++;
            size--;
        } else {
            break;
        }
    }
    *s++ = '\0';
}