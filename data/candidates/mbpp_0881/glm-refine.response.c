int __cdecl func0(int *list1, int size)
{
  int first_even = -1;
  int first_odd = -1;
  int i;

  // Find the first even number in the list
  for (i = 0; i < size; ++i)
  {
    if (list1[i] % 2 == 0)
    {
      first_even = list1[i];
      break;
    }
  }

  // Find the first odd number in the list
  for (i = 0; i < size; ++i)
  {
    if (list1[i] % 2 != 0)
    {
      first_odd = list1[i];
      break;
    }
  }

  // Return the sum of the first found even and odd numbers
  return first_even + first_odd;
}