int __cdecl func0(int n)
{
  int i; // [rsp+Ch] [rbp-FB4h]
  int f[1000]; // [rsp+10h] [rbp-FB0h] BYREF
  int na; // [rsp+FBCh] [rbp-4h]

  na = n;
  memset(f, 0, sizeof(f));
  f[0] = 0;
  f[1] = 1;
  for ( i = 2; i <= na; ++i )
    f[i] = f[i - 2] + f[i - 1];
  return f[na];
}