int __cdecl set_bit(int *ptr, int n)
{
  *ptr |= 1 << n;
  return *ptr;
}