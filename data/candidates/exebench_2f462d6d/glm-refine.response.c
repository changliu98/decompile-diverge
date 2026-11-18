int putdword(char *p, int w)
{
    *(short *)p = w;
    return w;
}