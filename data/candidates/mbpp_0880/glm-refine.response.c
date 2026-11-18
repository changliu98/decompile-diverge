const char *__cdecl func0(int a, int b, int c)
{
  // Calculates the discriminant of a quadratic equation: a*x^2 + b*x + c = 0
  int discriminant = b * b - 4 * a * c;

  if (discriminant > 0)
    return "2 solutions";
  if (discriminant == 0)
    return "1 solution";
  return "No solutions";
}