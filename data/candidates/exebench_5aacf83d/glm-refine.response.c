int __cdecl a_swap(volatile int *p, int v)
{
    // Atomically writes `v` to `*p` and returns the previous value of `*p`.
    // This is semantically equivalent to an atomic swap operation.
    return _InterlockedExchange(p, v);
}