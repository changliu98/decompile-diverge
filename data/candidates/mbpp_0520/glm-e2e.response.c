int func0(int *arr, int n) {
    int current_lcm = find_lcm(arr[0], arr[1]);
    for (int i = 2; i < n; i++) {
        current_lcm = find_lcm(current_lcm, arr[i]);
    }
    return current_lcm;
}