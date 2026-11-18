void __cdecl atomic_or(volatile size_t *x, size_t val)
{
  size_t expected = *x;
  size_t desired;

  do
  {
    desired = expected | val;
  }
  while (_InterlockedCompareExchange64((volatile signed __int64 *)x, desired, expected) != expected);
}