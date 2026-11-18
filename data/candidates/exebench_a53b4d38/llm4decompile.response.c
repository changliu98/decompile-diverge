void foo(int *x, int *y)
{
  int i;
  for (i = 0; i < 8; i++)
    if (y[i] != i + 2)
      break;

  if (i == 8 && *x == 1) {
    *x = i;
    for (i = 0; i < 8; i++)
      y[i] = i + 9;
  } else
    *x = 6;
}