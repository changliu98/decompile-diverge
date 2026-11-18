int atmc_fetch_and_add(volatile unsigned int *address, int value)
{
    int previous_value = _InterlockedExchangeAdd((volatile long *)address, value);
    return previous_value + value;
}