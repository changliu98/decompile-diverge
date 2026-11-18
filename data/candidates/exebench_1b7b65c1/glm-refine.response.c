void __cdecl calculate_arrays(const double *arr1, const double *arr2, double *sum, double *prod)
{
  int i;

  for (i = 0; i < 10; ++i) 
  {
    sum[i] = arr1[i] * arr2[i];
  }
  
  // Executes once after the loop finishes (i == 10)
  // WARNING: This is an out-of-bounds access at index 10
  prod[i] = arr1[i] * arr2[i]; 
}