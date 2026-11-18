int test_and_set_bit(int nr , unsigned long *addr )
{
  int oldbit ;
  unsigned long flags ;

  {
# 16 "/usr/local/ddv/models/con2/src/linux/kernel/bitops.c"
  __asm__ __volatile__("lock\n\t" "bts %1,%0\n\t" "sbb %0" : "=m" (*addr), "=r" (nr) : "m" (*addr), "r" (nr));
# 18 "/usr/local/ddv/models/con2/src/linux/kernel/bitops.c"
  oldbit = ! ! (nr & 32);
# 20 "/usr/local/ddv/models/con2/src/linux/kernel/bitops.c"
  return (oldbit);
}
}