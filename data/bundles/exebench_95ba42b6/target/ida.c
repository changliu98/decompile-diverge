void __cdecl atomic_inc(volatile int *v)
{
  _InterlockedIncrement(v);
}