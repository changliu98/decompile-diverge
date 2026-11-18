int func0(int A[], int n) {
  int left = 0;
  int right = n - 1;
  while (left <= right) {
    if (A[left] <= A[right]) {
      return left;
    }
    int mid = (left + right) / 2;
    int next = (mid + 1) % n;
    int prev = (mid - 1 + n) % n;
    if (A[mid] <= A[next] && A[mid] <= A[prev]) {
      return mid;
    } else if (A[mid] <= A[right]) {
      right = mid - 1;
    } else if (A[mid] >= A[left]) {
      left = mid + 1;
    }
  }
  return -1;
}