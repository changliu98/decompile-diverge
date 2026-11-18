void outfname(char *s) {
    while (*s != '\0') {
        s++;
    }
    s--;
    *s = 's';
}