int __cdecl func0(int n)
{
  int v2; // [rsp+8h] [rbp-8h]

  v2 = factorial(n + 1, 2 * n);
  return v2 / factorial(1, n);
}