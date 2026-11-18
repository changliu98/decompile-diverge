int putdword(char *p,int w)
{
    *p = w; *(p+1) = w >> 8;
    return (w);
}