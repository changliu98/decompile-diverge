void __cdecl minmax(int *arr, int *size, int *min, int *max)
{
  int current_val = *arr;

  // Update max if the current value is greater
  if (current_val > *max)
    *max = current_val;

  // Update min if the current value is smaller
  if (current_val < *min)
    *min = current_val;
}