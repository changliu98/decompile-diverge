static int putdword(unsigned char *p, int val)
{
 p[0] = val & 255;
 p[1] = (val >> 8) & 255;

 return val;
}