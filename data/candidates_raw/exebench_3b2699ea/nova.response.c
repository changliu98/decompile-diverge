void func0(char *str) {
    int i, j;
    char temp;
    for (i = 0; str[i]!= '\0'; i++)
        ;
    for (j = 0; j < i / 2; j++) {
        temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}