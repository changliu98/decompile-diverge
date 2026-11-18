int __cdecl func0(int n)
{
  int i;       
  int p_curr;  // Current term in the sequence P(i)
  int p_prev1; // Previous term P(i-1)
  int p_prev2; // Term before previous P(i-2)

  // Base cases: P(1) = 1, P(2) = 2
  if ( n <= 2 )
    return n;

  p_prev2 = 1; // P(1)
  p_prev1 = 2; // P(2)
  
  for ( i = 3; i <= n; ++i )
  {
    p_curr = p_prev2 + 2 * p_prev1;
    p_prev2 = p_prev1;
    p_prev1 = p_curr;
  }
  
  return p_prev1;
}