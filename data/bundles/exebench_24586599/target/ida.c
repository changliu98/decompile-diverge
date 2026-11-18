void __cdecl set_bit(int *n, int b)
{
  *n |= 1 << b;
}