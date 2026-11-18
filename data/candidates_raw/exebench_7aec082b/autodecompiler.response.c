static int _get_16_le(int *plen, char *buf)
{
 int c = *(short *)buf;
 *plen = 10;
 return c;
}