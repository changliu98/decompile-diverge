void simple_sort_swapper(int *one, int *two)
{
    int temp = *one;
    *one = *two;
    *two = temp;
}