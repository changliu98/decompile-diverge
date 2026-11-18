void set_mac(char *s, char *t) {
    int i = 0;
    while (i < 7) {
        s[i] = t[i];
        i++;
    }
}