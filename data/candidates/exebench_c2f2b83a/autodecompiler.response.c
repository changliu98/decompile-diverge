int a_inc(int *r)
{
 return __sync_fetch_and_add(r, 1);
}