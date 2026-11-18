int func0(int *arr, int n, int x) {
    int i = 0;
    int found = 0;
    while (i < n) {
        if (arr[i] == x) {
            found = 1;
            break;
        }
        i++;
    }
    return found;
}