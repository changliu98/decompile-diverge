char *func0(char *str, char *buf) {
    int i = 0;
    int j = 0;
    int underline = 1;
    while (1) {
        if (str[i]!= '\0') {
            if (str[i] == '_') {
                underline = 1;
            } else {
                if (underline) {
                    buf[j] = toupper(str[i]);
                    j++;
                    underline = 0;
                } else {
                    buf[j] = str[i];
                    j++;
                }
            }
        } else {
            break;
        }
        i++;
    }
    buf[j] = '\0';
    return buf;
}