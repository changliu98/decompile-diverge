int func0(int *a, int n) {
    int low = 0, high = n - 1, mid, res;
    while (low <= high) {
        mid = (low + high) / 2;
        if (a[mid] == mid + 1) {
            res = mid + 1;
            break;
        } else if (a[mid] == a[mid - 1]) {
            res = mid;
            break;
        } else if (a[mid]!= mid + 1) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return res;
}