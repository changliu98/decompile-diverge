int *func0(int *numbers, int size, int delimiter, int *out_size)
{
  int *out;
  int i; int j;
  int new_size;
  if (size > 0)
    new_size = size * 2 - 1;
  else
    new_size = 0;
  *out_size = new_size;
  out = (int *)malloc(*out_size * sizeof(int));
  if (size > 0)
    out[0] = numbers[0];
  for (i = 1, j = 1; i < size; i++, j += 2) {
    out[j] = delimiter;
    out[j + 1] = numbers[i];
  }
  return out;
}