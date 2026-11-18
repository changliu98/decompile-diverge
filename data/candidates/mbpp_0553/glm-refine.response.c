#include <math.h>

// This function concatenates an integer `a` and a non-negative integer `b` 
// by appending the digits of `b` to the right of `a` using floating-point arithmetic.
// Example: a = 123, b = 45 -> 123.0 + 45.0 / 10^2 = 123.45
float __cdecl concat_int_as_float(int a, int b)
{
  int digit_count; 

  // Calculate the number of base-10 digits in 'b'
  if (b != 0)
  {
    digit_count = 0;
    int temp = b;
    while (temp)
    {
      ++digit_count;
      temp /= 10;
    }
  }
  else
  {
    // If 'b' is 0, it conceptually represents "0", which is 1 digit
    digit_count = 1;
  }

  // Shift 'b' by its digit count to create a fractional part, then add to 'a'
  return (double)a + (double)b / pow(10.0, (double)digit_count);
}