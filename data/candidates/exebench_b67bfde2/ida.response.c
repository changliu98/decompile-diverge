int __cdecl wdl_atomic_incr(int *v)
{
  return _InterlockedIncrement(v);
}