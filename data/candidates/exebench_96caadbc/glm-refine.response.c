long __cdecl ihk_atomic_add_return(long i, long *v)
{
    return _InterlockedExchangeAdd64(v, i) + i;
}