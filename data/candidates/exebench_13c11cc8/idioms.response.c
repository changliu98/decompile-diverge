void sort_three(int *a, int *b, int *c)
{
  int tmp;
  if (*a > *b) {
    tmp = *b;
    *b = *a;
    *a = tmp;
  }
  if (*a > *c) {
    tmp = *c;
    *c = *a;
    *a = tmp;
  }
  if (*b > *c) {
    tmp = *b;
    *b = *c;
    *c = tmp;
  }
}