int __cdecl func0(int a)
{
  int i; // [rsp+0h] [rbp-10h]
  int num; // [rsp+4h] [rbp-Ch]
  int aa; // [rsp+8h] [rbp-8h]

  aa = a;
  if ( a < 2 )
    return 0;
  num = 0;
  for ( i = 2; i * i <= aa; ++i )
  {
    while ( !(aa % i) )
    {
      aa /= i;
      ++num;
    }
  }
  if ( aa > 1 )
    ++num;
  return num == 3;
}