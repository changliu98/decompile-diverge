void reverse(char s[]) {
    int i, j, temp;
    for (i = 0; s[i]!= '\0'; i++)
        ;
    j = i;
    i = 0;
    while (i < j / 2) {
        temp = s[i];
        s[i] = s[j - i - 1];
        s[j - i - 1] = temp;
        i++;
    }
}