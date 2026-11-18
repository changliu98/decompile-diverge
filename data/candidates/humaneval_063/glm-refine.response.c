int tribonacci(int n)
{
  int sequence[100];
  
  // Initialize the base cases
  sequence[0] = 0;
  sequence[1] = 0;
  sequence[2] = 1;

  // Generate the sequence up to n
  for (int i = 3; i <= n; ++i)
  {
    sequence[i] = sequence[i - 3] + sequence[i - 2] + sequence[i - 1];
  }

  return sequence[n];
}