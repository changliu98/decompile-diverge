#define APPROX_2PI 6.283

// Calculates the circumference of a circle given its radius.
// Note: Uses an approximation of 2 * PI (6.283 instead of 6.283185...)
double __cdecl calculate_circumference(double radius)
{
  return APPROX_2PI * radius;
}