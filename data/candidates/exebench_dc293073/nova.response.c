char *Q_strupr(char *str) {
    char *s = str;
    while (1) {
        if (*s) {
            if (*s >= 'a' && *s <= 'z') {
                *s = *s - 32;
            } else {
                *s = *s + 32;
            }
        } else {
            break;
        }
        s++;
    }
    return str;
}