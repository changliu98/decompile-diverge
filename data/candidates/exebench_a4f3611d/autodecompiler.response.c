int sync_test_and_change_bit(int nr , unsigned long volatile *addr )
{ int old ;
  int tmp ;

  {
  tmp = __sync_lock_test_and_set((unsigned int *)addr, (unsigned int )nr);
  old = tmp;
  return (old);
}
}