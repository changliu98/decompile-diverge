void inplace_swap(u64 *x, u64 *y)
{
    *y = (*x ^ *y);
    *x = (*x ^ *y);
    *y = (*x ^ *y);
}