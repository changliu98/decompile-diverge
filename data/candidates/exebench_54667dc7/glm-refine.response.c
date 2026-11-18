void __cdecl drv_generic_graphic_window(int pos, int size, int max, int *wpos, int *wsize)
{
  int start = pos;
  int end = pos + size;

  // Default to an empty window
  *wpos = 0;
  *wsize = 0;

  // Validate that the window has a positive size and intersects with the bounds [0, max]
  if ( pos <= max && end >= 0 && size >= 1 )
  {
    // Clip the start coordinate to the lower bound (0)
    if ( start < 0 )
      start = 0;

    // Clip the end coordinate to the upper bound (max)
    if ( end > max )
      end = max;

    // Return the clipped window position and size
    *wpos = start;
    *wsize = end - start;
  }
}