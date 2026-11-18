void func0(char *s, char *out)
{
    int i;
    for (i = 0; s[i] != 0; i++)
        out[i] = ((s[i] - 'a' + 1) % 26) + 'a';
    out[i] = 0;
}