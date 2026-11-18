void u64mul16(long a, long b, long *hi, long *lo)
{
  unsigned int a1 = a & 0xFFFF;
  unsigned int a2 = a >> 16;
  unsigned int b1 = b & 0xFFFF;
  unsigned int b2 = b >> 16;
  unsigned int p1 = a1 * b1;
  unsigned int p2 = a2 * b2;
  unsigned int p3 = a1 * b2;
  unsigned int p4 = a2 * b1;
  unsigned int p34 = p3 + p4;
  unsigned int p12 = p1 + p2;
  unsigned int p12hi = p12 >> 16;
  unsigned int p34hi = p34 >> 16;
  unsigned int p12lo = p12 & 0xFFFF;
  unsigned int p34lo = p34 & 0xFFFF;
  unsigned int p12hi2 = p12hi + p34hi;
  unsigned int p12hi2lo = p12hi2 & 0xFFFF;
  unsigned int p12hi2hi = p12hi2 >> 16;
  *hi = p12hi2hi + p2 + p12hi2lo + p34lo + (p12hi2hi + p2 + p12hi2lo + p34lo)>>16;
  *lo = p12lo + p34lo + (p12lo + p34lo)>>16;
}