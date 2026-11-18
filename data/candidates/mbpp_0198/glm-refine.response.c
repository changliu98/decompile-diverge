double __cdecl func0(int a, int b)
{
  if (a < 0 || b < 0)
    return -1.0;

  // The constant 3.0 * sqrt(3.0) evaluates to approximately 5.196152
  return (3.0 * sqrt(3.0) * pow((double)a, 2.0)) / (double)(4 * b);
}