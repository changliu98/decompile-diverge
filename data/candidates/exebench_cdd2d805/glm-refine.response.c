void __cdecl atomic_retain(volatile int *p)
{
  _InterlockedIncrement(p);
}