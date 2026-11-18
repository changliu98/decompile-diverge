int func0(int *arr, int n) {
    int max1 = -1, max2 = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0 && max1 == -1) {
            max1 = arr[i];
        }
        if (arr[i] % 2!= 0 && max2 == -1) {
            max2 = arr[i];
        }
        if (max1!= -1 && max2!= -1) {
            break;
        }
    }
    return max1 * max2;
}