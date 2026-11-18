void get_even_numbers(int a, int b, int *out, int *size)
{
  int i; int j;
  *size = 0;
  if (b < a) {
    i = b;
    b = a;
    a = i;
  }
  for (i = a; i <= b; i++) {
    if (i < 10 && i % 2 == 0) {
      out[(*size)++] = i;
    }
  }
}