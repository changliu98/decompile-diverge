int a_swap(int *addr, int val)
{
 int old;
 do {
  old = *addr;
 } while (!__sync_bool_compare_and_swap(addr, old, val));
 return old;
}