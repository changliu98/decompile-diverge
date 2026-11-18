void test(int *a, int *b, int *c, int *d, int *e)
{

  if (*a > 100) {
    goto ERROR;
  }

  if (*e > 100) {
    goto ERROR;
  }

  e = e + 1;

  e = e + 10;

  b = b + 1;

  *b = *b + 100;

  if (*c > 1000) {
    goto ERROR;
  }

  if (*d < 100) {
    goto ERROR;
  }

ERROR:
  return;

}