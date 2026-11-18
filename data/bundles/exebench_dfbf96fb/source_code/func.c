
static inline int a_swap(volatile int *x, int v)
{
 int old;
 do old = *x;
 while (!__sync_bool_compare_and_swap(x, old, v));
 return old;
}
