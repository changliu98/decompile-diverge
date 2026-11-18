void reverse(char s[])
{
    int len, i;
    char c;

    for (i = 0, len = 0; s[i] != '\0'; ++i)
        len++;

    for (i = 0; i < len / 2; ++i) {
        c = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = c;
    }
}