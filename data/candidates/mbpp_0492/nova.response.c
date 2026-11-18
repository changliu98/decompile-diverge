int func0(int *arr, int n, int key) {
    int low = 0, high = n - 1, mid, flag = 0;
    while (low <= high) {
        mid = (low + high) / 2;
        if (flag == 0)
            return flag;
        if (arr[mid] == key) {
            flag = 1;
            break;
        } else if (key < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return flag;
}