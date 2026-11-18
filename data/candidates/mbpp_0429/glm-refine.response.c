void __cdecl func0(const int *test_tup1, const int *test_tup2, int *res, int size)
{
    for (int i = 0; i < size; ++i)
    {
        res[i] = test_tup1[i] & test_tup2[i];
    }
}