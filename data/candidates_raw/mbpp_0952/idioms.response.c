int npr(int n, int r, int p)
{
  int i; int j; int k;
  int *arr;
  int *arrp;
  int npr;
  if (r > n - r)
    r = n - r;
  arr = (int *) (arrp = (int *) ( (char *) (arr) + ( ((sizeof(int)) * (r + 1)) + (sizeof(int) - 1) ) & ~(sizeof(int) - 1) ) );
  for (i = 0; i <= r; i++)
    arr[i] = 0;
  arr[0] = 1;
  for (i = 1; i <= n; i++)
  {
    int max;
    if (i < r + 1)
      max = i;
    else
      max = r + 1 - 1;
    for (j = max; j > 0; j--)
      arr[j] = (arr[j - 1] + arr[j]) % p;
  }
  npr = arr[r];
  return npr;
}