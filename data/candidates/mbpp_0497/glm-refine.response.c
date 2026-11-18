double __cdecl func0(double r, double h)
{
  // Calculates the total surface area of a right circular cone.
  // Formula: π * r * (r + sqrt(r^2 + h^2))
  // where:
  //   r = radius of the base
  //   h = height of the cone
  //   sqrt(r^2 + h^2) = slant height (l)
  //   π * r^2 = base area
  //   π * r * l = lateral surface area
  return 3.141592653589793 * r * (r + sqrt(r * r + h * h));
}