int func0(int *arr, int n) {
    int max = -1, min = -1, i = 0, j = 0;
    while (1) {
        if (i < n) {
            if (arr[i] % 2 == 0) {
                max = arr[i];
                break;
            }
        } else {
            break;
        }
        i++;
    }
    while (1) {
        if (j < n) {
            if (arr[j] % 2!= 0) {
                min = arr[j];
                break;
            }
        } else {
            break;
        }
        j++;
    }
    return max + min;
}