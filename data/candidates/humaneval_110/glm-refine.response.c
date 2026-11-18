const char *func0(int *list1, int size1, int *list2, int size2)
{
  int even_count = 0;
  int i;

  // Count even numbers in the first list
  for (i = 0; i < size1; ++i)
  {
    if (list1[i] % 2 == 0)
      ++even_count;
  }

  // Count even numbers in the second list
  for (i = 0; i < size2; ++i)
  {
    if (list2[i] % 2 == 0)
      ++even_count;
  }

  // If the total number of even elements is less than the size of the first list, return "false"
  if (even_count < size1)
    return "false";
  else
    return "true";
}