void reverse(char *str) {
    char *p = str;
    char temp;

    if (str == NULL) {
        return;
    }

    while (*p!= '\0') {
        p++;
    }

    p--;

    while (str < p) {
        temp = *str;
        *str = *p;
        *p = temp;
        str++;
        p--;
    }
}