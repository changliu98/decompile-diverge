int __cdecl valid(int *a, int n)
{
  int i;

  for ( i = 0; i < n - 2; ++i )
  {
    if ( a[i] < 0 )
      return 0;

    if ( a[i] > 0 )
    {
      a[i + 2] -= 3 * a[i];
      a[i + 1] -= 2 * a[i];
      a[i] = 0;
    }
  }

  // v3 is true if either of the last two elements is non-zero
  // The function returns 1 if v3 is false (i.e., both are zero), and 0 otherwise.
  return (a[n - 1] == 0) && (a[n - 2] == 0);
}