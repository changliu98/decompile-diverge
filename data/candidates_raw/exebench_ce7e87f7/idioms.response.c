void swap(int *a, int *b)
{
  int t = *a; *a = *b; *b = t;
  t = a[1]; a[1] = b[1]; b[1] = t;
  t = a[2]; a[2] = b[2]; b[2] = t;
  t = a[3]; a[3] = b[3]; b[3] = t;
}