int foo(int *a)
{
  int i, j;

  i = 0;
  j = 0;
  while (1)
    {
      if (j >= 11)
 break;
      a[j] = i++;
      j++;
    }
  return j + i;
}