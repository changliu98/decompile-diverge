int __cdecl func0(int num)
{
  int v2; // [rsp+Ch] [rbp-14h]
  int i; // [rsp+10h] [rbp-10h]
  int res_num; // [rsp+14h] [rbp-Ch]

  if ( num <= 1 )
    return 1;
  res_num = 0;
  for ( i = 0; i < num; ++i )
  {
    v2 = func0(i);
    res_num += func0(num - i - 1) * v2;
  }
  return res_num;
}