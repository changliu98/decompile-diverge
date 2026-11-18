void func0(int *tup1, int *tup2, int *tup_out, int size)
{
    int i;
    for(i = 0; i < size; i++)
        tup_out[i] = tup1[i] ^ tup2[i];
}