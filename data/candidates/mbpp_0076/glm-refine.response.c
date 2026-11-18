6
int __cdecl func0(int m, int n)
{
  int a = n < m ? n : m;  // min(m, n)
  int b = n < m ? m : n;  // max(m, n)

  return (a + 1) * a * (b - a) / 2       // triangular contribution from j > i
       + (2 * a + 1) * (a + 1) * a / 6;  // sum of squares: 1² + 2² + ... + a²
}