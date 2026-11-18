void encode_vector(char *c, int x, int y)
{
    c[0] = ' ' + (y >> 5);
    c[1] = 'a' + (y & 0x1f);
    c[2] = ' ' + (x >> 5);
    c[3] = '@' + (x & 0x1f);
    c[4] = '\0';
}