static inline unsigned int htonl(unsigned int x)
{
  if (sizeof(int) == 4)
    return x;
  else
    return (x + 1) & ~1;
}