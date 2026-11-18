int __cdecl func0(int n, int p)
{
  int i; // [rsp+0h] [rbp-10h]
  int out; // [rsp+4h] [rbp-Ch]

  out = 1;
  for ( i = 0; i < n; ++i )
    out = 2 * out % p;
  return out;
}