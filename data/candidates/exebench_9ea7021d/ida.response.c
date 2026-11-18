void __cdecl AdjustSpan(int *start, int *len, int max)
{
  if ( *start < 0 )
  {
    *len += *start;
    *start = 0;
  }
  if ( *len + *start > max )
    *len = max - *start;
}