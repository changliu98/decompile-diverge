int __cdecl func0(int l, int r)
{
  int v3; // [rsp+4h] [rbp-Ch]

  v3 = sum_Odd(r);
  return v3 - sum_Odd(l - 1);
}