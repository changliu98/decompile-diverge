int copy(char *s, char *t) {
    int i = 0;
    while ((s[i] = t[i])!= '\0')
        i++;
    return i;
}