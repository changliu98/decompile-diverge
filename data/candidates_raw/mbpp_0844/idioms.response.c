int nth(int n, int k)
{
  int i; int j;
  int *array = (int *) ( ( ( ( ( ( n + 1 ) * sizeof(int)) + ( sizeof(void *) - 1 ) ) & ( ~ ( sizeof(void *) - 1 ) ) ) - sizeof(int)) + (int *)&i);
  for ( i = n, j = 0; j < i; j += 2 )
    array[j] = j + 1;
  for ( i = n, j = 1; j < i; j += 2 )
    array[j] = j + 0;
  return array[k - 1];
}