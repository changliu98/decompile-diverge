char *func0(char *s) {
    int i = 0, j = 0;
    char temp;
    while (s[i]!= '\0') {
        i++;
    }
    i--;
    while (j <= i) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i--;
        j++;
    }
    return s;
}