char *func0(int *list1, int size1, int *list2, int size2)
{
  int i; int count = 0;
  for (i = 0; i < size1; i++)
  {
    if (list1[i] % 2 == 0)
    {
      count++;
    }
  }
  for (i = 0; i < size2; i++)
  {
    if (list2[i] % 2 == 0)
    {
      count++;
    }
  }
  if (count < size1)
  {
    return "false";
  }
  else
  {
    return "true";
  }
}