int __cdecl compare(int *min, int *mid, int *max)
{
  int temp;

  // Ensure the smallest value is in 'min'
  if (*min > *mid)
  {
    temp = *min;
    *min = *mid;
    *mid = temp;
  }
  if (*min > *max)
  {
    temp = *min;
    *min = *max;
    *max = temp;
  }

  // Ensure the largest value is in 'max'
  if (*mid > *max)
  {
    temp = *mid;
    *mid = *max;
    *max = temp;
  }

  return 0;
}