int __cdecl count_odd_numbers(const int *array_nums, int n)
{
    int count_odd = 0;

    for (int i = 0; i < n; ++i)
    {
        if (array_nums[i] % 2 != 0)
            ++count_odd;
    }

    return count_odd;
}