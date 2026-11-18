static char *parse_type(char *s, int *isref, int *isarray,
                        int *passin, int *passout, int *nullok,
                        int *isretained, int *isreturn)
{
    *isref = 0;
    *passin = 0;
    *passout = 0;
    *nullok = 1;
    *isarray = 0;
    *isretained = 0;
    *isreturn = 0;

    for (;;) {
        if (*s == '<') {
            *isref = 1;
            *passout = 1;
        } else if (*s == '>') {
            *isref = 1;
            *passin = 1;
        } else if (*s == '&') {
            *isref = 1;
            *passout = 1;
            *passin = 1;
        } else if (*s == '+') {
            *nullok = 0;
        } else if (*s == ':') {
            *isref = 1;
            *passout = 1;
            *nullok = 0;
            *isreturn = 1;
        } else if (*s == '#') {
            *isarray = 1;
        } else if (*s == '!') {
            *isretained = 1;
        } else {
            break;
        }
        s++;
    }

    return s;
}