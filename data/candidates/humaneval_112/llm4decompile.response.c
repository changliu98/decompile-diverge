void func0(char *s, char *c, char *result, char *palindrome)
{
    int i, j, k, len;
    char *t, *ch;
    int flag = 1;

    t = (char *)malloc(sizeof(char) * (strlen(s) + 1));

    for (i = 0, k = 0; s[i] != '\0'; i++) {
        for (j = 0; c[j] != '\0'; j++) {
            if (s[i] == c[j])
                break;
        }
        if (c[j] == '\0')
            t[k++] = s[i];
    }
    t[k] = '\0';

    len = strlen(t);
    for (i = 0; i < len / 2; i++) {
        if (t[i] != t[len - 1 - i]) {
            flag = 0;
            break;
        }
    }

    strcpy(result, t);
    strcpy(palindrome, flag ? "True" : "False");

    free(t);
}