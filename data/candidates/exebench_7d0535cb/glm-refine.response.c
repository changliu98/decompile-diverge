double __cdecl frexp(double x, int *exp)
{
  double abs_x = x;
  int n = 0;
  double sign = 1.0;

  // Check if the input is negative
  if (x < 0.0)
  {
    // Clear the sign bit to get the absolute value
    abs_x = -x; 
    sign = -1.0;
  }

  // Process only non-zero values
  if (abs_x != 0.0)
  {
    // Normalize the value to be within [0.5, 1.0)
    while (abs_x >= 1.0)
    {
      abs_x *= 0.5;
      ++n;
    }
    while (abs_x < 0.5)
    {
      abs_x *= 2.0;
      --n;
    }
  }

  *exp = n;
  return abs_x * sign;
}