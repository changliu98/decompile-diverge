char *func0(char *dest, char *src) {
    int i = 0;
    int j = 0;
    while (1) {
        if (src[i]!= '\0') {
            if (src[i] == '\b') {
                if (j > 0) {
                    j--;
                }
                if (j < 0) {
                    j = 0;
                }
            } else {
                dest[j++] = src[i];
            }
        } else {
            break;
        }
        i++;
    }
    dest[j] = '\0';
    return dest;
}