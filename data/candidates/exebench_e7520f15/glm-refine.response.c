int __cdecl CalcOffsetAndShift(const int x, const int y, size_t *offset, size_t *shift)
{
  // Validate bounds (unsigned comparison checks for negative values as well)
  if ((unsigned int)x >= MAX_X_COORDS || (unsigned int)y >= MAX_Y_COORDS)
    return -1;
    
  // Validate pointers
  if (!offset || !shift)
    return -1;

  // Calculate byte offset: (y / 8) gives the page/bank, multiplied by the row stride, plus x
  *offset = (size_t)(ROW_STRIDE * (y / Y_DIVISOR) + x);
  
  // Calculate bit shift: the remainder of y divided by 8 gives the bit position (0-7)
  *shift = (size_t)(y % Y_DIVISOR);
  
  return 0;
}