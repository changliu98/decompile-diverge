int __cdecl fetch_and_add(int *p, int i)
{
  return _InterlockedExchangeAdd(p, i);
}