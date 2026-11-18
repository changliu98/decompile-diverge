int __cdecl clip_wh(int *x, int *width, const int min_width, const int max_width)
{
  int xoff; // [rsp+0h] [rbp-24h]

  if ( *x >= min_width )
  {
    if ( *width + *x >= max_width )
      *width = max_width - *x;
    return 0;
  }
  else
  {
    xoff = min_width - *x;
    *width += *x;
    *x = min_width;
    return xoff;
  }
}