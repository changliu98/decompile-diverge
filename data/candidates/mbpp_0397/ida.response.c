int __cdecl func0(int a, int b, int c)
{
  if ( a <= b )
  {
    if ( a <= c )
    {
      if ( b >= c )
        return c;
      else
        return b;
    }
    else
    {
      return a;
    }
  }
  else if ( a >= c )
  {
    if ( b <= c )
      return c;
    else
      return b;
  }
  else
  {
    return a;
  }
}