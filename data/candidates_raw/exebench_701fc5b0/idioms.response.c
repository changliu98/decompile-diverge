int init(int *array)
{
  int i = 0; int j = 0;
  for (i = 0; i < 10; i++)
    array[i] = j++;
  return i + j;
}