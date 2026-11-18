void func0(int x, int base, char *out)
{
    int i = 0;
    int j = 0;
    char temp[32];
    while (x > 0)
    {
        temp[i] = (x % base) + '0';
        i++;
        x /= base;
    }
    while (i > 0)
    {
        i--;
        out[j] = temp[i];
        j++;
    }
    out[j] = '\0';
}