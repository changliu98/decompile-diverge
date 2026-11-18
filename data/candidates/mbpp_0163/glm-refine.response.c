#include <math.h>

// Mathematical Formula: Area of a regular polygon
// A = (s * l^2) / (4 * tan(PI / s))
// where:
// s = number of sides
// l = length of each side
double __cdecl calculate_regular_polygon_area(int sides, double side_length)
{
  return (double)sides * (side_length * side_length) / (4.0 * tan(M_PI / (double)sides));
}