void __cdecl factorial(double *fact)
{
  int i; // Loop counter, mapped from 'count'

  // Base case: 0! = 1
  *fact = 1.0;

  // Iteratively compute factorials: 1! through 19!
  // Note: The loop runs for i = 0 to 19. 
  // At i = 19, it computes fact[20] = 20 * fact[19].
  // This implies the caller's buffer must accommodate at least 21 elements (indices 0 to 20).
  for ( i = 0; i < 20; ++i )
  {
    fact[i + 1] = (double)(i + 1) * fact[i];
  }
}