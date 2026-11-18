int __cdecl atomic_add32_ret(int *cnt)
{
  return _InterlockedExchangeAdd(cnt, 1u);
}