void release(int *spinlock)

{
  int *spinlock_local;
  
  *spinlock = 0;
  return;
}