int __cdecl func0(double *array, int length)
{
  int sum; 
  int i; 

  sum = 0;
  for ( i = 0; i < length; ++i )
  {
    // Round the current double element to the nearest integer, 
    // cast it to int, and accumulate it into the sum.
    sum = (int)((double)sum + round(array[i]));
  }
  
  // Return the sum multiplied by the length of the array
  return length * sum;
}