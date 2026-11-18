int divide(int x, int y, int *r)
{
 int q;
 q = x / y;
 *r = x % y;
 return q;
}