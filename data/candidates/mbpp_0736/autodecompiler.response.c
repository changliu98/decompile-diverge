int func0(int *v, int n, int x)
{
    int mid;
    int high = n;
    int low = 0;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (v[mid] < x)
            low = mid + 1;
        else
            high = mid;
    }
    return (low);
}