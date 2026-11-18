void rotate(char str[], int n)
{
    char temp;
    int len = 0, j, i, k;

    for (char *p = str; *p != '\0'; p++, len++);

    for (j = 0; j < n; j++) {
        temp = str[len - 1];
        for (i = len - 1; i > 0; i--) {
            str[i] = str[i - 1];
        }
        str[0] = temp;
    }
}