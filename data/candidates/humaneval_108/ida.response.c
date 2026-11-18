int __cdecl func0(int *n, int size)
{
  int w; // [rsp+4h] [rbp-1Ch]
  int sum; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  int num; // [rsp+10h] [rbp-10h]

  num = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( n[i] <= 0 )
    {
      sum = 0;
      for ( w = abs(n[i]); w >= 10; w /= 10 )
        sum += w % 10;
      if ( sum - w > 0 )
        ++num;
    }
    else
    {
      ++num;
    }
  }
  return num;
}