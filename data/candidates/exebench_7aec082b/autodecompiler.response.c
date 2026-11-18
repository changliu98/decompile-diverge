static int g(int *plen, char *buf)
{
 int c = *(short *)buf;
 *plen = 10;
 return c;
}