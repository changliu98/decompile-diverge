int atomicCompareAndSwap(volatile int *var, int expected, int newValue)
{
    return _InterlockedCompareExchange(var, newValue, expected);
}