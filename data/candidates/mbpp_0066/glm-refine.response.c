int __cdecl count_non_negative(const int *values, int size)
{
    int non_negative_count = 0;

    for (int i = 0; i < size; ++i)
    {
        if (values[i] >= 0)
        {
            ++non_negative_count;
        }
    }

    return non_negative_count;
}