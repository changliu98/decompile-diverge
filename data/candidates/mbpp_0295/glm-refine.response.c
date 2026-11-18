int __cdecl func0(int number)
{
  int divisor; // [rsp+0h] [rbp-Ch]
  int sum;     // [rsp+4h] [rbp-8h]

  sum = 1; // 1 is a proper divisor for all numbers > 1
  
  // Iterate from 2 up to (number - 1) to find all other proper divisors
  for ( divisor = 2; divisor < number; ++divisor )
  {
    // If 'divisor' evenly divides 'number', it is a proper divisor
    if ( !(number % divisor) )
      sum += divisor;
  }
  
  return sum;
}