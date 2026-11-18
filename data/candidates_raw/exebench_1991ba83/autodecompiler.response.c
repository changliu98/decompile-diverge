int f_to_kHz(float f, long *k, long *m, long *b, long *r)
{
 *k = (long)(f * 255 / 100);
 return(1);
}