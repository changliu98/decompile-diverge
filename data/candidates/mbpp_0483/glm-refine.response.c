int __cdecl func0(int x)
{
  int factorial = 1; // Holds the running product of the factorial
  int k;             // Loop counter, representing the current step in the factorial

  for (k = 1; k < x; ++k)
  {
    factorial *= k;
    
    // If x divides the current factorial product, we've found our target 'k'
    if (!(factorial % x))
      return k;
  }
  
  // Fallback return if the loop completes without the condition being met.
  // (Note: mathematically, for x > 1, the condition is always met before or at x-1.
  // For x <= 1, the loop is skipped entirely, and it returns 0).
  return k - 1; 
}