void __cdecl atomic_and(volatile size_t *x, size_t val)
{
    size_t current = *x;
    while (_InterlockedCompareExchange64((volatile signed __int64 *)x, val & current, current) != current)
    {
        current = *x;
    }
}