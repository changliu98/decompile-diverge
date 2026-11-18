int get_size(int n)
{
  int size;
  if (n <= 4)
    size = n * sizeof(int);
  else
    size = (n - 4) * sizeof(int);
  return size + (4 * sizeof(int));
}