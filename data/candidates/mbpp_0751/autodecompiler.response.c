int func0(int array[], int n, int i)
{
    int left_child, right_child, parent;
    char condition1, condition2, condition3, condition4;

    if ((i * 2 + 2) > n)
    {
        condition1 = 1;
    }
    else
    {
        condition1 = (array[i] <= array[2 * i + 1]) & func0(array, n, 2 * i + 1);
    }

    if ((i * 2 + 2) == n)
    {
        condition2 = 1;
    }
    else
    {
        condition2 = (array[i] <= array[2 * i + 2]) & func0(array, n, 2 * i + 2);
    }

    condition3 = condition1 & condition2;

    condition4 = (condition1 & condition2) & (condition3 & condition4);

    return condition4;
}