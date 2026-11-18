int atomic_add32_ret(int *cnt)
{
  return _InterlockedExchangeAdd(cnt, 1);
}