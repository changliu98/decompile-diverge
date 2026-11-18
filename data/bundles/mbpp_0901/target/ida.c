int __cdecl func0(int n)
{
  int v1; // eax
  int j; // [rsp+0h] [rbp-1ACh]
  int number; // [rsp+4h] [rbp-1A8h]
  int factor_count; // [rsp+8h] [rbp-1A4h]
  int factors[100]; // [rsp+Ch] [rbp-1A0h]
  int i; // [rsp+1A0h] [rbp-Ch]
  int na; // [rsp+1A4h] [rbp-8h]

  na = n;
  if ( n <= 2 )
    return na;
  i = 2 * na;
  factor_count = 0;
  for ( number = na; number > 1; --number )
  {
    if ( 2 * number > na )
    {
      v1 = factor_count++;
      factors[v1] = number;
    }
  }
LABEL_8:
  for ( j = 0; ; ++j )
  {
    if ( j >= factor_count )
      goto LABEL_8;
    if ( i % factors[j] )
    {
      i += na;
      goto LABEL_8;
    }
    if ( j == factor_count - 1 && !(i % factors[j]) )
      break;
  }
  return i;
}