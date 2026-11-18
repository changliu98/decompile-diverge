void minmax(int *array, int size, int *min, int *max)
{
  if ( *min > *array )
    *min = *array;
  if ( *max < *array )
    *max = *array;
}