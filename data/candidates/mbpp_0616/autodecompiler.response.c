void func0(int *t1, int *t2, int *t3, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    t3[i] = t1[i] % t2[i];
  }
}