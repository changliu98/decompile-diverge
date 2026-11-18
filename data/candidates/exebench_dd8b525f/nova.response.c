void reverse(char *s) {
    int i = 0, j;
    char temp;
    while (s[i]!= '\0')
        i++;
    i--;
    if (s[i] == '\n')
        i--;
    for (j = 0; j < i; j++, i--) {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
    }
}