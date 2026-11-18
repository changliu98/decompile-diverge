void func0(char s[]) {
    int i, j, temp;
    for (i = 0; s[i]!= '\0'; i++)
        ;
    for (j = 0; j < i / 2; j++) {
        temp = s[j];
        s[j] = s[i - j - 1];
        s[i - j - 1] = temp;
    }
}