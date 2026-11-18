void clear_bit(int nr , unsigned long volatile *addr )
{ unsigned long mask ;
  unsigned long *tmp ;
  unsigned long old ;

  {
# 167 "concatenated.c"
  mask = (unsigned long )(1UL << ((nr) % 64));
# 168 "concatenated.c"
  tmp = addr + ((unsigned long )nr / 64UL);
# 169 "concatenated.c"
  old = *tmp;
# 170 "concatenated.c"
  *tmp &= ~ mask;
# 171 "concatenated.c"
  return;
}
}