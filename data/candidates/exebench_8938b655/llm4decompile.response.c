int itos(int i, char *s)
{
    int sign = i < 0 ? -1 : 1;
    unsigned int n = sign < 0 ? -i : i;
    int len = 0;
    do {
        len++;
        s[len] = n % 10 + '0';
        n /= 10;
    } while (n);
    s[0] = sign < 0 ? '-' : s[0];
    s[++len] = '\0';
    int i1 = 0, i2 = len - 1;
    while (i1 < i2) {
        char c = s[i1];
        s[i1] = s[i2];
        s[i2] = c;
        i1++;
        i2--;
    }
    return len;
}