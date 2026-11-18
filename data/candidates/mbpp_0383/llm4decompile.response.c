uint32_t func0(uint32_t n)
{
 uint32_t res = 0;
 uint32_t n_local = n;
 int i;
 for (i = 0; n_local > 0; i++)
 {
  if (i % 2 == 0)
  {
   res |= (1 << i);
  }
  n_local = n_local >> 1;
 }
 return res ^ n;
}