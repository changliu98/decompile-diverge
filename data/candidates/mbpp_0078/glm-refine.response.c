2
int __cdecl func0(int n)
{
  if (n & 1)
    return (n + 1) / 2;
  return n / 2 + __builtin_parity(n);
}