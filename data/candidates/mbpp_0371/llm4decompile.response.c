int func0(int A[], int left_element, int right_element) {
    int mid;
    if (left_element > right_element) {
        return left_element;
    }
    mid = left_element + (right_element - left_element) / 2;
    if (A[mid] == mid) {
        return func0(A, mid + 1, right_element);
    } else {
        return func0(A, left_element, mid - 1);
    }
}