int func0(const int *lst, int size)
{
  int sum = 0;

  for (int i = 0; ; ++i)
  {
    int index = 2 * i + 1;
    if (index >= size) {
      break;
    }

    // Check if the element at the odd index is an even number
    if (lst[index] % 2 == 0) {
      sum += lst[index];
    }
  }

  return sum;
}