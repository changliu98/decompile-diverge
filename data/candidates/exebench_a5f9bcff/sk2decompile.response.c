int foo(int *a, int *b) {
  int x = *a;
  int y = *b;
  x++;
  y++;
  *a = x;
  *b = y;
  return x + y;
}