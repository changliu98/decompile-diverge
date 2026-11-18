int __cdecl func0(int radius)
{
  int b; // [rsp+4h] [rbp-18h]
  int a; // [rsp+8h] [rbp-14h]
  int rectangles; // [rsp+14h] [rbp-8h]

  rectangles = 0;
  for ( a = 1; a < 2 * radius; ++a )
  {
    for ( b = 1; b < 2 * radius; ++b )
    {
      if ( b * b + a * a <= 2 * radius * 2 * radius )
        ++rectangles;
    }
  }
  return rectangles;
}