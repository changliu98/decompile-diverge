void func0(int a[], int n)
{
  int max_idx;
  while (n > 1)
  {
    max_idx = find_max_index(a, n);
    if (max_idx != n - 1)
    {
      reverse(a, 0, max_idx);
      reverse(a, 0, n - 1);
    }
    n--;
  }
}