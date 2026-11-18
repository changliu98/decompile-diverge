void
grad1(int n, float *rgb, float *hsl)
{
 int h = ((int)hsl[0] & 15);
 rgb[0] = h & 7;
 rgb[0] += 1;
 if (h & 8)
  rgb[0] ^= 0x80000000;
}