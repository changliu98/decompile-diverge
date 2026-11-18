void set_be16(unsigned char *p, int val)
{
 p[0] = (unsigned char)((val >> 0) & 0xff);
 p[1] = (unsigned char)((val >> 8) & 0xff);
}