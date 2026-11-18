void func0(char s[], int n) {
    int i, j;
    char temp;
    for (i = 0, j = n - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}