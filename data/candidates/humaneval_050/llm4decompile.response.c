void func0(char *s, int encode)
{
    size_t i, len;
    int shift = encode ? 5 : 21;

    len = strlen(s);
    for (i = 0; i < len; i++) {
        s[i] = ((s[i] - 'a') + shift) % 26 + 'a';
    }
}