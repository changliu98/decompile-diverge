static int test_and_set_bit(int nr , unsigned long *addr )
{
  int oldbit ;

  {
# 16 "/usr/local/ddv/models/con2/src/linux/kernel/resource.c"
  oldbit = (int )((unsigned long )((int volatile )(*(int volatile *)addr)) << nr >> 31);
# 17 "/usr/local/ddv/models/con2/src/linux/kernel/resource.c"
  *(int volatile *)addr |= (unsigned long )(1 << nr);
# 18 "/usr/local/ddv/models/con2/src/linux/kernel/resource.c"
  return (oldbit);
}
}