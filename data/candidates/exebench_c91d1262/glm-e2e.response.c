int ISORegexp__get_cclass(const char *str, int pos, int *len, int *start, int *end, int *neg) {
    int ret;
    char c = str[pos];
    
    if (c == '^') {
        pos++;
        *neg = 1;
    } else {
        *neg = 0;
    }
    
    c = str[pos];
    
    switch (c) {
        case ' ':
            *len = 1;
            return 3;
        case '%':
            pos++;
            *len = 2;
            c = str[pos];
            switch (c) {
                case 'd': return 2;
                case 's': return 1;
                case 'a': return 4;
                case 'l': return 5;
                case 'u': return 6;
                case 'w': return 7;
                case 'p': return 9;
                default:
                    *start = pos;
                    *end = pos;
                    return 8;
            }
        case '[':
            *start = pos + 2;
            while (str[pos] != '\0' && str[pos] != ']') {
                pos++;
            }
            *end = pos - 1;
            *len = pos - *start + 1;
            return 8;
        default:
            *len = 1;
            *start = pos;
            *end = pos;
            return 8;
    }
}