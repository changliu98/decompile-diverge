void func0(char s[]) {
    int i, j, temp;
    for (i = 0; s[i]!= '\0'; i++)
        ;
    j = 0;
    while (j < i - 1) {
        temp = s[j];
        s[j] = s[i - 1];
        s[i - 1] = temp;
        j++;
        i--;
    }
}