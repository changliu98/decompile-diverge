char *__cdecl func0(int a, int b, int n)
{
  unsigned int i;

  // Iterate through all possible values for x (i) such that a*x <= n
  for ( i = 0; (int)(a * i) <= n; ++i )
  {
    // Check if (n - a*x) is perfectly divisible by b
    if ( !((int)(n - a * i) % b) )
    {
      // If so, a solution is found. Format and store the result.
      sprintf(func0_result, "x = %d, y = %d", i, (unsigned int)((int)(n - a * i) / b));
      return func0_result;
    }
  }
  
  // Return the string literal if no valid integer solution is found
  return "No solution";
}