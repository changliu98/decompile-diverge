int __cdecl func0(int l, int r)
{
    // Number of even integers in the range [l, r]
    int count_r = r / 2;
    int count_l = (l - 1) / 2;

    // Sum of even integers from 2 to r
    int sum_r = (count_r + 1) * count_r;

    // Sum of even integers from 2 to l-1
    int sum_l = (l + 1) * count_l / 2;

    // Total sum of even integers in the range [l, r]
    return sum_r - sum_l;
}