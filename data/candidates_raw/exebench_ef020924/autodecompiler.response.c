void SwapEndian64(unsigned long *in)
{
 unsigned long tmp = *in;
 *in = ((tmp & 0xff) << 56) | ((tmp & 0xff00) << 40) | ((tmp & 0xff0000) << 24) |
       ((tmp & 0xff000000) << 8) | ((tmp >> 8) & 0xff000000) | ((tmp >> 24) & 0xff0000) |
       ((tmp >> 40) & 0xff00) | (tmp >> 56);
}