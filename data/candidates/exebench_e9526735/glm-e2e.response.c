void removeslave(int *arr, int count) {
    int i = 9;
    while (i >= 0) {
        if (arr[i] != 0) {
            arr[i] = 0;
            count--;
        }
        if (count == 0) {
            break;
        }
        i--;
    }
}