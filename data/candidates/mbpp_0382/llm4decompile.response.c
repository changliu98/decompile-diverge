int func0(int *A, int n) {
    int left = 0;
    int right = n - 1;
    int mid;
    while (left <= right) {
        if (A[left] <= A[right]) {
            return left;
        }
        mid = (left + right) / 2;
        if (A[mid] <= A[(mid + 1) % n] && A[mid] <= A[(mid - 1 + n) % n]) {
            return mid;
        }
        if (A[mid] <= A[right]) {
            right = mid - 1;
        } else if (A[left] <= A[mid]) {
            left = mid + 1;
        }
    }
    return -1;
}