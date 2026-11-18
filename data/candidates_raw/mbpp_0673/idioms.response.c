int get_id(int *list, int size)
{
  int id = 0;
  int i;
  for (i = 0; i < size; i++)
    id = id * 10 + list[i];
  return id;
}