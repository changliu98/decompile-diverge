static int _f_to_kHz(float f, long *k, long *m, long *b, long *s)
{
 *k = (long)(f*255/100);
 return(1);
}