/**
 * @brief Calculates the surface area of a sphere.
 * 
 * Mathematical Formula: 4 * PI * r^2
 * The magic number 12.56637061435917 is an approximation of 4 * PI.
 * 
 * @param radius The radius of the sphere.
 * @return double The surface area of the sphere.
 */
double __cdecl sphere_surface_area(double radius)
{
  // Preserving the exact literal to maintain original floating-point semantics
  return 12.56637061435917 * radius * radius;
}