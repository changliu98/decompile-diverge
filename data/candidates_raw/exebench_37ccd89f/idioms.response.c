void mod(int *a, int *b)
{
  int d = *a / *b;
  *b = *a - *b * d;
  *a = d;
}