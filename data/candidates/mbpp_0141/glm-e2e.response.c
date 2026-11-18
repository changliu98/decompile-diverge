void func0(int *arr, int n) {
    for (int i = n; i > 1; i--) {
        int max_idx = find_max_index(arr, i);
        if (max_idx != i - 1) {
            reverse(arr, 0, max_idx);
            reverse(arr, 0, i - 1);
        }
    }
}