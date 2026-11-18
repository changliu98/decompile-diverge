char *func0(char *str, char *buf) {
    int i = 0, j = 1;
    int k = 0;
    while (1) {
        if (str[k]!= '\0') {
            if (str[k] == '_') {
                j = 1;
                continue;
            }
            if (j) {
                buf[i++] = toupper(str[k]);
                j = 0;
            } else {
                buf[i++] = str[k];
            }
        } else {
            break;
        }
        k++;
    }
    buf[i] = '\0';
    return buf;
}