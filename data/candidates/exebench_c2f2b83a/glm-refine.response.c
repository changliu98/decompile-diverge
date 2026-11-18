Returns the resulting incremented value
int __cdecl a_inc(volatile int *p)
{
    return _InterlockedIncrement(p);
}