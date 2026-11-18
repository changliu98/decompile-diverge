void wordstore(char *p, int w)
{
    p[0] = w & 0xff;
    p[1] = (w >> 8) & 0xff;
}