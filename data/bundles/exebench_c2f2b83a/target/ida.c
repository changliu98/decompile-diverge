void __cdecl a_inc(volatile int *p)
{
  _InterlockedIncrement(p);
}