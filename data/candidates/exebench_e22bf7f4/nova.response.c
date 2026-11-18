void reverse(char s[]) {
    int i = 0, j = 0;
    char temp;
    while (s[i]!= '\0') {
        j++;
    }
    for (i = 0; i < j / 2; i++) {
        temp = s[i];
        s[i] = s[j - 1 - i];
        s[j - 1 - i] = temp;
    }
}