int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-1A4h]
  int f[100]; // [rsp+4h] [rbp-1A0h]
  int na; // [rsp+1A0h] [rbp-4h]

  na = n;
  f[0] = 0;
  f[1] = 0;
  f[2] = 2;
  f[3] = 0;
  for ( i = 4; i <= na; ++i )
    f[i] = f[i - 4] + f[i - 3] + f[i - 2] + f[i - 1];
  return f[na];
}