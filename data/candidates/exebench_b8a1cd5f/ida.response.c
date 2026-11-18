int __cdecl atomic32_decrement(int *dest)
{
  return _InterlockedDecrement(dest);
}