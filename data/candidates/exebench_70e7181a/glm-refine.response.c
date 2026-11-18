void __cdecl split(int sx1, int sy1, int sx2, int sy2, int *uy1, int *uy2, int *ly1, int *ly2, int num_pixels)
{
  // Calculate the width of the region. 
  // The '+ 1' accounts for the inclusive coordinate bounds (e.g., x1=0 to x2=0 has a width of 1).
  int width = sx2 - sx1 + 1;

  // Proceed only if the region has a valid, positive width
  if (width > 0)
  {
    // Calculate how many full rows the 'num_pixels' will occupy.
    // Integer division naturally floors the result, leaving any remainder in the lower section.
    int rows_upper = num_pixels / width;

    // Upper section bounds (inclusive)
    *uy1 = sy1;
    *uy2 = sy1 + rows_upper - 1;

    // Lower section bounds (inclusive)
    // It starts immediately after the upper section ends.
    *ly1 = sy1 + rows_upper;
    *ly2 = sy2;
  }
}