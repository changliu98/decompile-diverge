void __cdecl adjust_point(int *n)
{
  if ( *n >= 0 )
  {
    if ( *n > 100 )
      *n = 100;
  }
  else
  {
    *n = 0;
  }
}