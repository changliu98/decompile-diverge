void get_vector_modulo(int *a, int *m)
{
  int i;
  for (i = 0; i < 3; i++) {
    a[i] %= m[i];
    if (a[i] < 0)
      a[i] += m[i];
  }
}