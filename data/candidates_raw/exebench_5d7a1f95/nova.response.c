void func0(char *dest, char *src) {
    int i = 0;
    int j = 0;

    while (1) {
        switch (src[j]) {
        case '\\':
            dest[i] = '\\';
            i++;
            dest[i] = '\\';
            i++;
            break;
        case '\'':
            dest[i] = '\\';
            i++;
            dest[i] = '\'';
            i++;
            break;
        case '\"':
            dest[i] = '\\';
            i++;
            dest[i] = '\"';
            i++;
            break;
        case '?':
            dest[i] = '\\';
            i++;
            dest[i] = '?';
            i++;
            break;
        case '<':
            dest[i] = '\\';
            i++;
            dest[i] = '<';
            i++;
            break;
        case '>':
            dest[i] = '\\';
            i++;
            dest[i] = '>';
            i++;
            break;
        case '|':
            dest[i] = '\\';
            i++;
            dest[i] = '|';
            i++;
            break;
        case '`':
            dest[i] = '\\';
            i++;
            dest[i] = '`';
            i++;
            break;
        default:
            dest[i] = src[j];
            j++;
            i++;
            break;
        }
    }
}