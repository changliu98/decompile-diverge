void minmax(int *item, int *size, int *min, int *max)
{
  if (*item > *max)
    *max = *item;
  if (*item < *min)
    *min = *item;
}