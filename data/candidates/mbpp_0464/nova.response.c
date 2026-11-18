int func0(int *arr, int n, int k) {
    int i = 0;
    bool found = false;
    while (i < n) {
        if (arr[i] == k) {
            found = true;
            break;
        }
        found = false;
        i++;
    }
    return found;
}