void release(int *spinlock)
{
  *spinlock = 0;
}