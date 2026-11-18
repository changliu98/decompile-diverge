__int64 __cdecl func0(int n, int *primes, int primesSize)
{
  __int64 min_val; // rdx
  int next_idx; // ecx
  __int64 result; // [rsp+8h] [rbp-48h]
  __int64 next_ugly; // [rsp+10h] [rbp-40h]
  int j; // [rsp+18h] [rbp-38h]
  int ja; // [rsp+18h] [rbp-38h]
  int i; // [rsp+1Ch] [rbp-34h]
  int ia; // [rsp+1Ch] [rbp-34h]
  __int64 *candidates; // [rsp+20h] [rbp-30h]
  int *indices; // [rsp+28h] [rbp-28h]
  __int64 *uglies; // [rsp+30h] [rbp-20h]

  // Allocate memory for the sequence of ugly numbers, 
  // the indices tracking which ugly number each prime should multiply next,
  // and the current candidate values for each prime.
  uglies = (__int64 *)malloc(8LL * n);
  indices = (int *)calloc(primesSize, 4uLL);
  candidates = (__int64 *)malloc(8LL * primesSize);
  
  *uglies = 1LL;
  
  // Initialize candidates with the given primes
  for ( i = 0; i < primesSize; ++i )
    candidates[i] = primes[i];
    
  // Generate the sequence of 'n' ugly numbers
  for ( ia = 1; ia < n; ++ia )
  {
    // Find the minimum candidate value
    next_ugly = *candidates;
    for ( j = 1; j < primesSize; ++j )
    {
      if ( candidates[j] < next_ugly )
        next_ugly = candidates[j];
    }
    
    uglies[ia] = next_ugly;
    
    // Update candidates that match the minimum value to avoid duplicates
    for ( ja = 0; ja < primesSize; ++ja )
    {
      if ( candidates[ja] == next_ugly )
      {
        min_val = primes[ja];
        next_idx = indices[ja] + 1;
        indices[ja] = next_idx;
        candidates[ja] = uglies[next_idx] * min_val;
      }
    }
  }
  
  result = uglies[n - 1];
  
  // Free allocated memory
  free(uglies);
  free(indices);
  free(candidates);
  
  return result;
}