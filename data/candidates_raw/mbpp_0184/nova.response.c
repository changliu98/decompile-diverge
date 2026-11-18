int func0(int *arr, int n, int x) {
    int i = 0;
    bool found = false;
    while (i < n &&!found) {
        if (arr[i] < x) {
            found = false;
        } else if (arr[i] == x) {
            found = true;
        }
        i++;
    }
    return found;
}