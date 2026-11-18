char *__cdecl func0(int n)
{
  int i; // [rsp+Ch] [rbp-14h]
  int count; // [rsp+10h] [rbp-10h]

  count = 0;
  for ( i = 1; i < (int)sqrt((double)n) + 2; ++i )
  {
    if ( !(n % i) )
    {
      if ( n / i == i )
        ++count;
      else
        count += 2;
    }
  }
  if ( count % 2 )
    return "Odd";
  else
    return "Even";
}