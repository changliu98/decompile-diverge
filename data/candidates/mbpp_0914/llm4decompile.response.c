int func0(char *s)
{
    int i;
    int len = strlen(s);
    for (i = 0; i < len - 2; i++) {
        if (s[i] != s[i + 2]) {
            return 0;
        }
    }
    if (s[0] == s[1]) {
        return 0;
    }
    return 1;
}