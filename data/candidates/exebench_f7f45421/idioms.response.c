void swap(int *a, int *b)
{
  int t = *a;
  *a = *a + *b;
  *b = t - *b;
  *a = t - *a;
}