void
clear_bit (int nr , unsigned long volatile *addr )
{
  unsigned long old ;
  int new ;

  {
# 277 "concatenated.c"
  old = addr[0UL];
# 278 "concatenated.c"
  new = (int )old & ~ ((int )1 << nr);
# 279 "concatenated.c"
  addr[0UL] = (unsigned long )new;
# 280 "concatenated.c"
  return;
}
}