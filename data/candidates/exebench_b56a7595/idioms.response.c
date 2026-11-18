void rotr(int *a, int *b, int *c)
{
  int tmp = *c;
  *c = *b;
  *b = *a;
  *a = tmp;
}