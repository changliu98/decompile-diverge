char *jstrescapecpy(char *dest, const char *src) {
    int i = 0;
    int j = 0;
    char *p;

    if (src == NULL) {
        dest[0] = '\0';
        p = dest;
    } else {
        while (src[i]!= '\0') {
            switch (src[i]) {
            case '&':
                dest[j++] = '\\';
                dest[j++] = '&';
                break;
            case '<':
                dest[j++] = '\\';
                dest[j++] = '<';
                break;
            case '>':
                dest[j++] = '\\';
                dest[j++] = '>';
                break;
            default:
                dest[j++] = '_';
                i++;
                break;
            }
        }
        dest[j++] = '\0';
        p = dest;
    }
    return p;
}