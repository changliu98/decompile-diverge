int str_linecount(char *s, int lim, int *nl) {
    int c, i;

    for (i = 1; (c = *s++)!= '\0'; i++) {
        if (c == '\n') {
            (*nl)++;
            *nl = 0;
        } else {
            (*nl)++;
            if (*nl >= lim) {
                i++;
                *nl = 0;
            }
        }
    }
    return i;
}