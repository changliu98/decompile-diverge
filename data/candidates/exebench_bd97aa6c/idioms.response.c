void subpixels(unsigned long p, unsigned long *a, unsigned long *r, unsigned long *g, unsigned long *b)
{
  unsigned long a_val = p / (256 * 256 * 256);
  unsigned long r_val = p / (256 * 256) % 256;
  unsigned long g_val = p / 256 % 256;
  unsigned long b_val = p % 256;
  *a = a_val;
  *r = r_val;
  *g = g_val;
  *b = b_val;
}