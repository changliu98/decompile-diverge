int func0(int *arr, int low, int high)
{
    int mid;
    int ans;

    if(low > high)
    {
        ans = high + 1;
    }
    else if(arr[low] != low)
    {
        ans = low;
    }
    else
    {
        mid = (low + high)/2;

        if(arr[mid] == mid)
        {
            ans = func0(arr, mid + 1, high);
        }
        else
        {
            ans = func0(arr, low, mid);
        }
    }

    return ans;
}