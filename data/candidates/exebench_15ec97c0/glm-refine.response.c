double __cdecl GO_frexp(double x, int *exp)
{
  double abs_x;
  int n = 0;
  double sign = 1.0;

  if (x < 0.0) 
  {
    // Equivalent to: *(_QWORD *)&xa = *(_QWORD *)&x ^ 0x8000000000000000LL;
    abs_x = -x;
    sign = -1.0;
  } 
  else 
  {
    abs_x = x;
  }

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