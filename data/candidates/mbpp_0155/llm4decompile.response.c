uint32_t func0(uint32_t n)
{
 int i;
 uint32_t res;
 uint32_t mask;

 res = 0;
 mask = 1;
 for (i = 0; n > 0; i++) {
  if (i % 2 == 1) {
   res |= mask;
  }
  mask <<= 1;
  n >>= 1;
 }

 return n ^ res;
}