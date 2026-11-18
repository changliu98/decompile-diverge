unsigned int swizzle(unsigned int i, unsigned int limit)
{
 unsigned int out = 0;
 while (limit)
 {
  out = (out << 1) | (i & 1);
  i >>= 1;
  limit >>= 1;
 }
 return out;
}