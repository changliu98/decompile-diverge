void __cdecl release(volatile int *spinlock)
{
  *spinlock = 0;
}