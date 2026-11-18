void __cdecl limit2_i32(int *x, int lower, int upper)
{
  if ( *x < upper )
  {
    if ( *x <= lower )
      *x = lower;
  }
  else
  {
    *x = upper;
  }
}