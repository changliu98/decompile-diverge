int ok_cp1251(char *header, int size)
{
  int i;
  for (i = 1; i < size; i++)
    if (header[i] == -104)
      return (0);
  return (1);
}