int __cdecl func0(int n)
{
  int ans; // [rsp+0h] [rbp-14h]
  int i; // [rsp+4h] [rbp-10h]
  int count; // [rsp+8h] [rbp-Ch]

  if ( n % 2 )
    return (n + 1) / 2;
  count = 0;
  for ( i = 0; i < 32; ++i )
    count += (n >> i) & 1;
  ans = n / 2;
  if ( count % 2 )
    ++ans;
  return ans;
}