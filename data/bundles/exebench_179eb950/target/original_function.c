static inline void
swap_int(int *x, int *y)
{
     *y = *x ^ *y;
     *x = *y ^ *x;
     *y = *x ^ *y;
}