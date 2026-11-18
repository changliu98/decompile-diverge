int obdRevConvert_2D(float f, long *k, long *m, long *b, long *s)
{
 *k = (long)((f + 100.0) / 0.78125);
 return(1);
}