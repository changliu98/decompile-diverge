bool func0(int *arr, int n) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            found = true;
            break;
        }
    }
    return found;
}