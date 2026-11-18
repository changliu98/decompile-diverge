unsigned __int64 __cdecl ihk_atomic_add_long_return(long i, long *v)
{
  return i + _InterlockedExchangeAdd64(v, i);
}