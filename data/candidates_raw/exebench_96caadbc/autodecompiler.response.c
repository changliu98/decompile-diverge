static int add(int x, int *y)
{
 int old = x;
 __sync_fetch_and_add(y, x);
 return x += old;
}