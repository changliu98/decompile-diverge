int last_element(int *array, int n, int step)
{
    int last = array + (n-1)*step;
    return *(last);
}