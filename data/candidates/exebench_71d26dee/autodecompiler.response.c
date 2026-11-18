static int obdRevConvert_2C(float f, long *k, long *m, long *b, long *s)
{
 *k = (long)(f*255/100);
 return(1);
}