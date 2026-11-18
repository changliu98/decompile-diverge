void copy_string(char *dest, char *src, int n) {
    int i = 0;
    bool not_null = true;

    while (not_null) {
        if (i < n) {
            dest[i] = src[i];
            not_null = dest[i]!= '\0';
        } else {
            break;
        }

        if (not_null) {
            i++;
        }
    }
}