unsigned long multmodp(unsigned long a, unsigned long b)
{
 unsigned long res = 0;
 unsigned long val = b;
 unsigned long mask = 0x80000000;

 while (mask) {
  if (a & mask)
   res ^= val;
  mask >>= 1;
  if (val & 1)
   val = (val >> 1) ^ 0xedb88320;
  else
   val = (val >> 1);
 }
 return res;
}