char *func0(char *s, int d)
{
    char *t;
    int len;
    int i;

    len = strlen(s);
    t = malloc((size_t)(len + 1));

    for (i = 0; i < len; i++) {
        t[i] = s[(i + d) % len];
    }
    t[len] = '\0';

    return t;
}