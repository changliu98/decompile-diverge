int __cdecl func0(int radius)
{
  int x; // [rbp-14h]
  int y; // [rbp-18h]
  int count; // [rbp-8h]

  count = 0;
  
  // Iterate over a 2*radius by 2*radius bounding box
  for ( x = 1; x < 2 * radius; ++x )
  {
    for ( y = 1; y < 2 * radius; ++y )
    {
      // Check if the point (x, y) lies inside a circle of radius 2*radius
      // Simplified from: y * y + x * x <= 2 * radius * 2 * radius
      if ( x * x + y * y <= 4 * radius * radius )
        ++count;
    }
  }
  
  return count;
}