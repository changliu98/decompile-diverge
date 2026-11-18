int __cdecl calculate_sign_and_magnitude(int *arr, int arr_size)
{
  int i;
  int sign;
  int sum;

  if (arr_size == 0)
    return -32768;

  sum = 0;
  sign = 1;

  for (i = 0; i < arr_size; ++i)
  {
    sum += abs(arr[i]);

    if (arr[i] == 0)
      sign = 0;

    if (arr[i] < 0)
      sign = -sign;
  }

  return sign * sum;
}