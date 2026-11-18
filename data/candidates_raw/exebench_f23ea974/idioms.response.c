void swap(int *a)
{
  int tmp = *a;
  *a = *(a + 1);
  *(a + 1) = tmp;
}