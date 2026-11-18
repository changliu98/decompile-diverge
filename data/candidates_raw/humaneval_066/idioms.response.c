int get_sum(char *name)
{
  int sum = 0;
  int i = 0;
  for (i = 0; name[i]; i++)
  {
    if (name[i] >= 'A' && name[i] <= 'Z')
    {
      sum += name[i];
    }
  }
  return sum;
}