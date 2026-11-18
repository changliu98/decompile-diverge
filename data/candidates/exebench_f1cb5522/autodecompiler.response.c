void argorder(int x, int y, int *a, int *b)
{
 if(x > y) {
  int t = x;
  x = y;
  y = t;
 }
 *a = x;
 *b = y;
}