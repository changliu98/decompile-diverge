int __cdecl func0(int n)
{
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    int odd = 2 * i - 1;
    sum += odd * odd * odd * odd * odd; // (2i - 1)^5
  }
  return sum;
}