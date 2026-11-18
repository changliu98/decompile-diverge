int __cdecl inicializa(int *vec, int n, int *min, int *max)
{
  // If the number of elements is odd, initialize with the first element
  if (n % 2)
  {
    *min = *vec;
    *max = *vec;
    return 1;
  }
  
  // If the number of elements is even, initialize with the first two elements
  if (*vec >= vec[1])
  {
    *min = vec[1];
    *max = *vec;
  }
  else
  {
    *min = *vec;
    *max = vec[1];
  }
  
  return 2;
}