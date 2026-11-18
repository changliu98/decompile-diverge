int __cdecl count_non_positive(int *list, int list_size)
{
    int neg_count = 0;

    for (int i = 0; i < list_size; ++i)
    {
        if (list[i] <= 0)
            ++neg_count;
    }

    return neg_count;
}