int __cdecl func0(int n)
{
  int sum = 0;
  
  // The loop iterates from 1 to n, calculating the sum of the fourth powers 
  // of the first 'n' odd numbers: 1^4 + 3^4 + 5^4 + ... + (2n-1)^4
  for (int i = 1; i <= n; ++i)
  {
    int odd = 2 * i - 1;
    sum += odd * odd * odd * odd;
  }
  
  return sum;
}