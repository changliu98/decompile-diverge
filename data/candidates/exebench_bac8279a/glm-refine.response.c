char __cdecl bppm_symbol(float *x)
{
  float x0 = x[0];
  float x1 = x[1];
  float x2 = x[2];
  float sum = x1 + x2;

  // Threshold for dominance (2/3)
  if (x0 > 0.667f)
    return '.';   // 46
  if (x1 > 0.667f)
    return '(';   // 40
  if (x2 > 0.667f)
    return ')';   // 41

  // Triangle inequality checks
  if (x0 >= sum)
    return ',';   // 44
  if (sum >= x0)
    return ':';   // 58

  // Ratio checks for the remaining cases
  float ratio1 = x1 / sum;
  if (ratio1 > 0.667f)
    return '{';   // 123

  float ratio2 = x2 / sum;
  if (ratio2 > 0.667f)
    return '}';   // 125

  return '|';     // 124
}