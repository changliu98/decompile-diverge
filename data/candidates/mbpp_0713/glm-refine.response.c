bool __cdecl func0(const bool *test_tup, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (!test_tup[i])
            return false;
    }
    return true;
}