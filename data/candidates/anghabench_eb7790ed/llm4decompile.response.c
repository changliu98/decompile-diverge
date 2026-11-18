int __sw_hweight32(uint32_t w)
{
 w = w - ((w >> 1) & 0x55555555);
 w = (w & 0x33333333) + ((w >> 2) & 0x33333333);
 w = (w + (w >> 4)) & 0x0F0F0F0F;
 w = w + (w >> 8);
 w = w + (w >> 16);
 return w & 0xFF;
}