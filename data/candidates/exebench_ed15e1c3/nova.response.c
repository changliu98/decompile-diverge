void reverse(char s[]) {
    unsigned int i, j;
    char temp;

    for (i = 0; s[i]!= '\0'; i++)
        ;

    j = i;

    for (i = 0; i < j / 2; i++) {
        temp = s[i];
        s[i] = s[j - i - 1];
        s[j - i - 1] = temp;
    }
}