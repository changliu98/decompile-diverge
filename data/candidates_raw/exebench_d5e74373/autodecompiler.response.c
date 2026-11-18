int
d2c_to_h (float f, long *d1, long *d2, long *d3, long *d4)
{
 f += 40.0;
 f *= 10.0;
 *d1 = (long) f / 256L;
 *d2 = (long) f % 256L;
 return(2);
}