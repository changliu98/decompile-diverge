int doit(int *a, int b)
{
  int result;
  if (*a > b) {
    *a = b;
    result = 1;
  } else {
    result = 0;
  }
  return result;
}