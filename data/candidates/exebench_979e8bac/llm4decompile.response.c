void swap(int *p, int *q)
{
    int temp;
    temp = *q;
    *q = *p;
    *p = temp;
}