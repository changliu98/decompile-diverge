int float_cmp(void *a, void *b)
{
  if (*(float *)a == *(float *)b)
    return 0;
  return (*(float *)a < *(float *)b ? -1 : 1);
}