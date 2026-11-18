int foo(int *a)
{
  int i, j;

  for (i = 0, j = 0; i < 10; i++)
    a[i] = j++;

  return i + j;
}