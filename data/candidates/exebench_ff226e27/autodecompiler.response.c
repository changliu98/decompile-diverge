static int atomic_add(int x, int *y)
{
 return __sync_fetch_and_add(y, x);
}