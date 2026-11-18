int func0(int *arr, int size)
{
    int i;
    int lcm = find_lcm(arr[0], arr[1]);

    for (i = 2; i < size; i++) {
        lcm = find_lcm(lcm, arr[i]);
    }

    return lcm;
}