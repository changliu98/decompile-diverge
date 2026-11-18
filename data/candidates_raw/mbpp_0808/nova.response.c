int func0(int *arr, int n, int k) {
    bool found = false;
    int i = 0;
    while (i < n) {
        if (arr[i] == k) {
            found = true;
            break;
        }
        i++;
    }
    return found? 1 : 0;
}