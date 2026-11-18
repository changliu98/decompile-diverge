void decrease_order(int *num1, int *diff)
{
    int temp;

    if (*num1 < *diff)
    {
        temp = *num1;
        *num1 = *diff;
        *diff = temp;
    }
}