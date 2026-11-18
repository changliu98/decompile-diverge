int ilog2(size_t n)
{
 int i = 0;
 for (;;) {
  if ((size_t)1 << i > n)
   return i;
  i++;
 }
}