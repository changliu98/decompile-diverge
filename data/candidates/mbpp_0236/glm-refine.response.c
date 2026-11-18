Optimized and annotated version
int __cdecl func0(int N, int K)
{
  // Base case: N must be at least K to form a valid configuration
  if ( N >= K )
  {
    // Let D = N - K (the difference between N and K)
    // The original expression can be algebraically simplified:
    // (N - 2K + 2) = (N - K) - K + 2 = D - K + 2
    // (N - 2K + 1) = (N - K) - K + 1 = D - K + 1
    // (N - K + 2)  = D + 2
    // (N - K + 1)  = D + 1
    //
    // This yields the simplified formula:
    // ((D - K + 2) * (D - K + 1)) / 2 + ((D + 2) * (D + 1)) / 2
    //
    // The terms (x + 2) * (x + 1) / 2 represent the sum of integers from 1 to (x + 1),
    // which is the formula for triangular numbers: T(x + 1).
    
    int D = N - K;
    
    // Calculate the two triangular number components
    int term1 = (D - K + 2) * (D - K + 1) / 2;
    int term2 = (D + 2) * (D + 1) / 2;
    
    return term1 + term2;
  }
  else
  {
    // Invalid case
    return -1;
  }
}