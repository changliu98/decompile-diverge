void release(volatile int *spinlock)

{
  *spinlock = 0;
}