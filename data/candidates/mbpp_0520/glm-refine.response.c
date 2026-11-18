int __cdecl func0(int *arr, int count)
{
    if (count <= 0)
        return 0; // Fallback for empty array (preserves standard behavior)

    int lcm = find_lcm(arr[0], arr[1]);

    for (int i = 2; i < count; ++i)
    {
        lcm = find_lcm(lcm, arr[i]);
    }

    return lcm;
}