int func0(int *arr, int l, int r) {
    int mid;
    if (l > r)
        mid = r + 1;
    else if (arr[l]!= l)
        mid = l;
    else {
        mid = (l + r) / 2;
        if (arr[mid] == mid)
            mid = func0(arr, mid + 1, r);
        else
            mid = func0(arr, l, mid);
    }
    return mid;
}