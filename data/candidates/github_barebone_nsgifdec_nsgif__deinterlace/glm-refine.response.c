bool __cdecl nsgif__deinterlace(uint32_t height, uint32_t *y, uint8_t *step)
{
  // Advance the current y-coordinate by the step interval.
  // The original mask `& 0xF` is equivalent to a direct dereference since 
  // step is only ever assigned 2, 4, 8, or 24 (all < 16).
  *y += *step;

  // If the new y-coordinate is within bounds, we are done for this pass.
  if (*y < height)
    return true;

  // If we've exceeded the image height, move to the next interlace pass.
  switch (*step)
  {
    case 24:
      *y = 4;
      *step = 8;
      return *y < height;

    case 8:
      *y = 2;
      *step = 4;
      return *y < height;

    case 4:
      *y = 1;
      *step = 2;
      return *y < height;

    default:
      // Includes `step == 2` (final pass exhausted) or any invalid state.
      return false;
  }
}