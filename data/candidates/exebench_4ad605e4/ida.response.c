int __cdecl atmc_fetch_and_add(volatile unsigned int *address, int value)
{
  return _InterlockedExchangeAdd((volatile signed __int32 *)address, value) + value;
}