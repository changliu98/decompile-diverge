bool func0(int *arr, int n) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    return found;
}