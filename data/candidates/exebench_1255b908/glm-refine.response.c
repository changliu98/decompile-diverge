int __cdecl clip_wh(int *x, int *width, const int min_x, const int max_x)
{
  // If the start position is already within bounds
  if (*x >= min_x)
  {
    // If the end position exceeds the right bound, clamp the width
    if (*x + *width > max_x)
      *width = max_x - *x;
    
    return 0;
  }
  else
  {
    // Calculate how far the start position is outside the left bound
    int offset = min_x - *x;
    
    // Shift the start position to the left bound
    *x = min_x;
    
    // Subtract the offset from the width to maintain the right boundary.
    // (Mathematically equivalent to: *width = *width + *x_old - min_x)
    *width += *x; 
    
    return offset;
  }
}