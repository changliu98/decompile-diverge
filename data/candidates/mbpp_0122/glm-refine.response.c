int __cdecl func0(int n)
{
  int v1; // Temporary variable for storing the current result index
  int temp; // Temporary variable for swapping elements during bubble sort
  int j_0; // Inner loop variable for bubble sort
  int i_0; // Outer loop variable for bubble sort
  int j;   // Inner loop variable for the sieve
  int i;   // Outer loop variable for the sieve
  int resultIndex; // Counter for the number of valid numbers found
  int result[3000]; // Array to store numbers with exactly 3 distinct prime factors
  int primes[3000]; // Sieve array: tracks the count of distinct prime factors for each number
  int na; // Local copy of the input parameter n

  na = n;
  
  // Initialize the sieve array to 0 for all elements.
  // In this sieve, primes[i] will store the negative count of distinct prime factors of i.
  memset(primes, 0, sizeof(primes));
  
  resultIndex = 0;
  
  // Modified Sieve of Eratosthenes
  // Instead of just marking primes, this counts the number of distinct prime factors for each number.
  for ( i = 2; i < 3000; ++i )
  {
    // If primes[i] is 0, it means i has not been marked by any smaller prime, so i is prime.
    if ( !primes[i] )
    {
      // Mark the prime number itself with 1 (though this value isn't used further for primes).
      primes[i] = 1;
      
      // Iterate through all multiples of the prime i
      for ( j = 2 * i; j < 3000; j += i )
      {
        // Decrement the count for the multiple. 
        // Since it's decremented, a value of -3 means the number has exactly 3 distinct prime factors.
        if ( --primes[j] == -3 )
        {
          // Store the number in the result array and increment the result counter
          v1 = resultIndex++;
          result[v1] = j;
        }
      }
    }
  }
  
  // Sort the result array in ascending order using Bubble Sort
  // This is necessary because numbers with 3 prime factors are discovered out of order 
  // (e.g., 30 is found before 42, but 42 is found before 60).
  for ( i_0 = 0; i_0 < resultIndex - 1; ++i_0 )
  {
    for ( j_0 = 0; j_0 < resultIndex - i_0 - 1; ++j_0 )
    {
      if ( result[j_0] > result[j_0 + 1] )
      {
        // Swap the elements if they are in the wrong order
        temp = result[j_0];
        result[j_0] = result[j_0 + 1];
        result[j_0 + 1] = temp;
      }
    }
  }
  
  // Return the n-th element (1-indexed) from the sorted result array
  return result[na - 1];
}