void func0(char *s, int *letters, int *digits) {
    int l = 0, d = 0;
    while (*s) {
        if (*s >= '0' && *s <= '9') {
            d++;
        } else if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')) {
            l++;
        }
        s++;
    }
    *letters = l;
    *digits = d;
}