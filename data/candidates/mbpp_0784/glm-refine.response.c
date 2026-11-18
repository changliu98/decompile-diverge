int __cdecl func0(int *list1, int n)
{
  int first_even = -1;
  int first_odd = -1;

  for (int i = 0; i < n; ++i)
  {
    int val = list1[i];

    if ((val % 2 == 0) && first_even == -1)
      first_even = val;

    if ((val % 2 != 0) && first_odd == -1)
      first_odd = val;

    if (first_even != -1 && first_odd != -1)
      break;
  }

  return first_odd * first_even;
}