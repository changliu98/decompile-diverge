// Recursive multiplication via repeated addition.
// Computes x * y without using the '*' operator.
// Behavior is undefined when y == INT_MIN (negation overflows -> infinite recursion).
int __cdecl multiply(int x, int y)
{
  if (y < 0)
    return -multiply(x, -y);   // handle negative multiplier
  if (y == 0)
    return 0;                  // base case: x * 0
  if (y == 1)
    return x;                  // base case: x * 1
  return multiply(x, y - 1) + x;  // inductive step: x * y = x * (y-1) + x
}