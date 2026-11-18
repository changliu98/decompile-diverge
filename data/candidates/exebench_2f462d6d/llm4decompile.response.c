int putdword(char *p, int w)
{
 p[0] = w & 0xff;
 p[1] = (w >> 8) & 0xff;
 p[2] = (w >> 16) & 0xff;
 p[3] = (w >> 24) & 0xff;
 return w;
}