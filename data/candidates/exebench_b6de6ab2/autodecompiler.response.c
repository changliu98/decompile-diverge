void
reduce_grid_address(int *a, int *b)
{
 int i;

 for (i = 0; ; i++)
  if (i < 4)
   a[i] -= b[i] * ((a[i] > b[i]/2) & 1);
  else
   return;
}