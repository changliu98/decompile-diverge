void
reduce_grid_address(int *a, int *b)
{
 long i;

 for (i = 0; ; i++) {
  if (i >= 4)
   break;
  a[i] -= b[i] * ((a[i] > b[i]/2) ? 1 : 0);
 }
}