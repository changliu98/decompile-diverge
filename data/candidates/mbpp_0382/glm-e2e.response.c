int func0(int *arr, int n) {
    int left = 0;
    int right = n - 1;
    int mid;
    int next;
    int prev;

    while (left <= right) {
        if (arr[left] <= arr[right]) {
            return left;
        }

        mid = (left + right) / 2;
        next = (mid + 1) % n;
        prev = (mid - 1 + n) % n;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }

        if (arr[mid] <= arr[right]) {
            right = mid - 1;
        } else if (arr[mid] >= arr[left]) {
            left = mid + 1;
        }
    }

    return -1;
}