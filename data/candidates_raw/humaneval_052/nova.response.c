int func0(int *arr, int n, int k) {
    int i = 0;
    bool flag = false;
    while (i < n) {
        if (arr[i] >= k) {
            flag = true;
            break;
        }
        i++;
    }
    return flag;
}