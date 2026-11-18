void __cdecl atomic_inc(volatile int *a)
{
  _InterlockedIncrement(a);
}