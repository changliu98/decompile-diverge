int test_and_change_bit(int i, unsigned int *p)
{
    int oldbit = !(*p & (1 << i));
    *p ^= (1 << i);
    return oldbit;
}