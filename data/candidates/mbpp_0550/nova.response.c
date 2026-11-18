int func0(int *arr, int left, int right) {
    int mid;
    int max;
    if (right < left)
        max = arr[0];
    else if (right == left)
        max = arr[right];
    else {
        mid = left + (right - left) / 2;
        if (mid < right && arr[mid + 1] < arr[mid])
            max = arr[mid];
        else if (mid > left && arr[mid - 1] < arr[mid])
            max = arr[mid];
        else if (arr[left] > arr[mid])
            max = func0(arr, left, mid - 1);
        else
            max = func0(arr, mid + 1, right);
    }
    return max;
}