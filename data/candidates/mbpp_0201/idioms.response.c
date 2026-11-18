int func0(char *list[], int size)
{
  int i;
  for (i = 1; i < size; i++)
  {
    if (strcmp(list[0], list[i]) != 0)
    {
      return 0;
    }
  }
  return 1;
}