static int obdRevConvert_45(float f, long *k, long *m, long *b, long *s)
{
 *k = (long)(f*255/100);
 return(1);
}