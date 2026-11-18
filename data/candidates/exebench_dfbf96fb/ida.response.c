int __cdecl a_swap(volatile int *x, int v)
{
  volatile int v2; // ett
  volatile int old; // [rsp+0h] [rbp-10h]

  do
  {
    old = *x;
    v2 = *x;
  }
  while ( v2 != _InterlockedCompareExchange(x, v, *x) );
  return old;
}