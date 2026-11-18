int func0(int exponent)
{
  double result;
  // Calculate n-th power of a constant value stored at _DAT_00102010
  result = pow(_DAT_00102010,(double)exponent);
  // Compute (dVar1 - DAT_00102008)^2 - 2 and return as integer
  return (int)(result - DAT_00102008) * (int)(result - DAT_00102008) + -2;
}