int __cdecl func0(int n)
{
  int j; 
  int current_sum; 
  int exponent; 
  int i; 
  int count; 
  int remainder; 

  remainder = n;
  count = 0;
  
  // Iterate through possible prime factors up to sqrt(n)
  for ( i = 2; i * i <= n; ++i )
  {
    exponent = 0;
    
    // Factor out all occurrences of the prime factor `i`
    while ( !(remainder % i) )
    {
      remainder /= i;
      ++exponent;
    }
    
    current_sum = 0;
    
    // Find the maximum number of times we can subtract the sequence 
    // 1, 2, 3... from the exponent without going negative.
    for ( j = 1; j + current_sum <= exponent; ++j )
    {
      current_sum += j;
      ++count;
    }
  }
  
  // If there is a prime factor left greater than sqrt(n), it contributes exactly 1 to the count
  if ( remainder != 1 )
    ++count;
    
  return count;
}