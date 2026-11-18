void func0(char *s, char *t) {
    int i = 0;
    while (s[i]!= '\0') {
        t[i] = tolower(s[i]);
        i++;
    }
    t[i] = '\0';
}