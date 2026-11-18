int __cdecl func0(int a, int b, int d)
{
  int min_val;
  int max_val;

  // Determine the minimum and maximum of 'a' and 'b'
  if (a >= b) {
    min_val = b;
  } else {
    min_val = a;
  }

  if (a <= b) {
    max_val = b;
  } else {
    max_val = a;
  }

  // If 'd' is greater than or equal to the maximum of 'a' and 'b'
  if (d >= max_val) {
    // Equivalent to ceil(d / max_val)
    return (d + max_val - 1) / max_val;
  }

  // If 'd' is 0
  if (!d) {
    return 0;
  }

  // If 'd' is exactly equal to the minimum of 'a' and 'b'
  if (d == min_val) {
    return 1;
  }

  // For any other value of 'd' less than max_val
  return 2;
}