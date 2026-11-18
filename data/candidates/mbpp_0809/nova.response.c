bool func0(int *arr, int *brr, int n) {
    bool ans = true;
    int i = 0;
    while (i < n) {
        if (arr[i] <= brr[i]) {
            ans = false;
            break;
        }
        i++;
    }
    return ans;
}