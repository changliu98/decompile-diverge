void __cdecl swap(int *a)
{
  int min_idx; 
  int max_idx; 
  int i; 

  // Find the index of the minimum element in the array a[0..9]
  min_idx = 0;
  for ( i = 0; i < 10; ++i )
  {
    if ( a[i] < a[0] )
      min_idx = i;
  }

  // Find the index of the maximum element in the array a[0..9]
  max_idx = 0;
  for ( i = 0; i < 10; ++i )
  {
    if ( a[i] > a[0] )
      max_idx = i;
  }

  // Swap a[0] and a[min_idx] using addition/subtraction (XOR swap equivalent)
  a[0] += a[min_idx];
  a[min_idx] = a[0] - a[min_idx];
  a[0] -= a[min_idx];

  // Swap a[9] and a[max_idx] using addition/subtraction (XOR swap equivalent)
  a[9] += a[max_idx];
  a[max_idx] = a[9] - a[max_idx];
  a[9] -= a[max_idx];
}