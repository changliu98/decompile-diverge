int __cdecl func0(int n, int x, int y)
{
  int k;
  int ans = INT_MIN; // Initialized to 0x80000000

  // Iterate through all possible values of k from 0 to n
  for (k = 0; k <= n; ++k)
  {
    // Check if the remainder of k divided by x equals y
    if (k % x == y && ans < k)
    {
      ans = k;
    }
  }

  // Validate the result. If no valid k was found, ans remains INT_MIN.
  // The condition (ans < 0 || ans > n) catches both INT_MIN and any unexpected overflow.
  if (ans < 0 || ans > n)
    return -1;
  else
    return ans;
}