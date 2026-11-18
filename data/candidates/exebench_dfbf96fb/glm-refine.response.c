int __cdecl a_swap(volatile int *x, int v)
{
  int old;
  int expected;

  do
  {
    old = *x;
    expected = old;
  }
  while ( _InterlockedCompareExchange(x, v, expected) != expected );

  return old;
}