void swap_float_4(float *tnf4)
{
 int *tni4=(int *)tnf4;
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
     ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));
}