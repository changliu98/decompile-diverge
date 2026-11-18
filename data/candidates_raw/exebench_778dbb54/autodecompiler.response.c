static int
f_to_s16_be(float f, int *hi, int *lo, int *sign, int *exp)
{
 f = f * 255 / 100;
 *hi = (int)f / 256;
 *lo = (int)f % 256;
 return 2;
}