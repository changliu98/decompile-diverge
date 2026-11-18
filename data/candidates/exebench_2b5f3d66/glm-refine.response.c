int __cdecl gcdEx(int a, int b, int *x, int *y)
{
  // Base case: when b becomes 0, the GCD is a. 
  // The identity for GCD(a, 0) is: a*1 + 0*0 = a
  if (b == 0) 
  {
    *x = 1;
    *y = 0;
    return a;
  }

  // Recursive call: gcdEx(b, a % b, x, y)
  // After this call returns, x and y are temporarily updated to satisfy:
  // b * (*x) + (a % b) * (*y) = gcd
  int gcd = gcdEx(b, a % b, x, y);

  // We need to adjust x and y so they satisfy the current level's equation:
  // a * x_new + b * y_new = gcd
  // 
  // Mathematically, the back-substitution step is:
  // x_new = *y
  // y_new = *x - (*y) * (a / b)
  //
  // To do this in C without a temporary variable, we swap and adjust:
  int temp_x = *x;
  *x = *y;                  // x_new = old_y
  *y = temp_x - *y * (a / b); // y_new = old_x - old_y * quotient

  return gcd;
}