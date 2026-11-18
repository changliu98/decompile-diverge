int obdRevConvert_52(float f, long *k, long *m, long *b, long *r)
{
 *k = (long)(f * 255 / 100);
 return(1);
}