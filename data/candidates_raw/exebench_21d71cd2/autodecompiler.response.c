static int
float_to_bcd2(float x, long *bcdh, long *bcdl, long *bcdm, long *bcds)
{
 x /= 10;
 *bcdh = (long) x / 256;
 *bcdl = (long) x % 256;
 return(2);
}