unsigned __int64 __cdecl xchg8(unsigned __int64 *ptr, unsigned __int64 x)
{
  return _InterlockedExchange64((volatile __int64 *)ptr, x);
}