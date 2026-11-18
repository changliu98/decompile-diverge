void set(int *array, int index)
{
  *array = *array | (1 << index);
}