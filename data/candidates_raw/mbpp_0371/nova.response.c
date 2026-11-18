int func0(int *arr, int l, int r) {
    int mid;
    if (l > r)
        mid = l;
    else {
        mid = l + (r - l) / 2;
        if (arr[mid] == mid)
            mid = func0(arr, mid + 1, r);
        else
            mid = func0(arr, l, mid - 1);
    }
    return mid;
}