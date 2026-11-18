void strrev(char s[]) {
    int i, j;
    char temp;
    for (i = 0; s[i]!= '\0'; i++)
        ;
    i = i - 1;
    for (j = 0; j < i; j++) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i--;
    }
}