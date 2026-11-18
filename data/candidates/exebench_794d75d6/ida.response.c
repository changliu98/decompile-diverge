void __cdecl AdjustSpan2(int *start, int *u, int *len, int max)
{
  if ( *start < 0 )
  {
    *len += *start;
    *u -= *start;
    *start = 0;
  }
  if ( *len + *start > max )
    *len = max - *start;
}