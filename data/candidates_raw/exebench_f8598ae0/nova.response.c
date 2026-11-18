int func0(float *arr, int size, float key) {
    int low, high, mid;
    if (key <= arr[0])
        return 0;
    if (key >= arr[size - 1])
        return (size - 1);

    low = 0;
    high = size;
    mid = size;
    while (high - low > 1) {
        mid = low + (high - low) / 2;
        if (key <= arr[mid - 1])
            high = mid;
        else
            low = mid;
    }
    return (high - 1);
}