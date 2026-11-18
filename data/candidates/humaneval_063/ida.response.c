int __cdecl func0(int n)
{
  int i; // [rsp+Ch] [rbp-1A4h]
  int ff[100]; // [rsp+10h] [rbp-1A0h] BYREF
  int na; // [rsp+1ACh] [rbp-4h]

  na = n;
  memset(ff, 0, sizeof(ff));
  ff[1] = 0;
  ff[2] = 1;
  for ( i = 3; i <= na; ++i )
    ff[i] = ff[i - 3] + ff[i - 2] + ff[i - 1];
  return ff[na];
}