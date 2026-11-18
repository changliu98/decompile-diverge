double __cdecl func0(double a)
{
  // sqrt(5.0 * (sqrt(5.0) + sqrt(5.0) + 5.0)) simplifies to sqrt(5.0 * (2.0 * sqrt(5.0) + 5.0))
  // which is the exact formula for the area of a regular pentagon with side length 'a'
  double sqrt_5 = sqrt(5.0);
  double pentagon_const = sqrt(5.0 * (2.0 * sqrt_5 + 5.0));
  
  // pow(a, 2.0) is mathematically equivalent to a * a
  return (pentagon_const * (a * a)) / 4.0;
}