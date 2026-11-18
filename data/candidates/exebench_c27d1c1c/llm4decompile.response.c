void reverse(char *s)
{
    char *r = s;
    char t;

    if (s == NULL)
        return;

    while (*s != '\0')
        s++;

    s--;

    while (s > r) {
        t = *s;
        *s = *r;
        *r = t;
        r++;
        s--;
    }
}