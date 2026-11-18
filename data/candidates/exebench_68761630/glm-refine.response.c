void __cdecl a_or(volatile int *p, int v)
{
  _InterlockedOr(p, v);
}