int func0(int *arr, int n) {
    int low = 0;
    int high = n - 1;
    int ret;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] != mid + 1) {
            if (arr[mid - 1] == mid) {
                ret = mid + 1;
                return ret;
            }
        }

        if (arr[mid] == mid + 1) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    ret = -1;
    return ret;
}