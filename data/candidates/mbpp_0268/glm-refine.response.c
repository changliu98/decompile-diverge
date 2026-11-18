int __cdecl func0(int n)
{
  // Expands to: 6n^2 - 6n + 1
  // This sequence represents the centered hexagonal numbers (A003215)
  return 6 * n * (n - 1) + 1;
}