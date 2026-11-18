void byte2bits(char c, char *s)
{
    int z;
    for (z = 7; z >= 0; z--)
        *s++ = ((c >> z) & 1) ? '1' : '0';
    *s = '\0';
}