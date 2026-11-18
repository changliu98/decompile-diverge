void std::swap<int>(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}