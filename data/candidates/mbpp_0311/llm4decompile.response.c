uint32_t func0(uint32_t n)
{
 uint32_t pos = 0;
 uint32_t tmp = n;
 uint32_t i;

 if ((n & (n + 1)) == 0)
  return n;

 for (i = 0; tmp != 0; i++) {
  if ((tmp & 1) == 0)
   pos = i;
  tmp >>= 1;
 }

 return n | (1 << pos);
}