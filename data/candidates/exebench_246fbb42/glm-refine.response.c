int __cdecl mean3(int a, int b, int c, int white, int *err)
{
  int m = (a + b + c) / 3;

  if (err)
  {
    int diff_a = abs(a - m);
    int diff_b = abs(b - m);
    int diff_c = abs(c - m);
    
    // The original nested conditions evaluate to the maximum of the three differences
    *err = max(diff_a, max(diff_b, diff_c));
  }

  if (a < white && b < white && c < white)
    return m;

  // If any value is >= white, return white if m <= white, otherwise return m
  // This is logically equivalent to: return max(white, m);
  return (m <= white) ? white : m;
}