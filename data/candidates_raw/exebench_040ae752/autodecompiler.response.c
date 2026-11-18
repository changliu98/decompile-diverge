void *clear_bit_ret2(int nr , unsigned long *addr )
{
  int old ;
  unsigned long tmp ;

  {
# 279 "concatenated.c"
  old = (int )((unsigned long )(*addr) & (unsigned long )(1 << (unsigned int )nr));
# 281 "concatenated.c"
  tmp = (unsigned long )(*addr) & (unsigned long )(1 << (unsigned int )nr);
# 281 "concatenated.c"
  *addr = (unsigned long )(*addr) & (unsigned long )(1UL << (unsigned int )nr);
# 283 "concatenated.c"
  return ((void *)tmp);
}
}