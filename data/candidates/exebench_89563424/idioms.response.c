void f(int *a)
{
  int tmp = a[0];
  a[0] = a[1];
  a[1] = tmp;
}