void __cdecl simplify(int *numerator, int *denominator)
{
  int lowestNum; // [rsp+0h] [rbp-18h]
  int commonNum; // [rsp+4h] [rbp-14h]

  if ( *numerator >= *denominator || *numerator <= 0 )
  {
    if ( *denominator <= 0 )
      lowestNum = *numerator;
    else
      lowestNum = *denominator;
  }
  else
  {
    lowestNum = *numerator;
  }
  while ( lowestNum )
  {
    if ( *numerator % lowestNum || *denominator % lowestNum )
    {
      if ( lowestNum <= 0 )
        ++lowestNum;
      else
        --lowestNum;
    }
    else
    {
      commonNum = lowestNum;
      lowestNum = 0;
    }
  }
  if ( commonNum == -1 )
    commonNum = 1;
  *numerator /= commonNum;
  *denominator /= commonNum;
}