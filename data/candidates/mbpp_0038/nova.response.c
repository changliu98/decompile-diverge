double func0(int *arr, int n) {
    int max = -1, min = -1, i = 0;
    while (i < n) {
        if (arr[i] % 2 == 0) {
            max = arr[i];
            break;
        }
        i++;
    }
    for (int j = 0; j < n; j++) {
        if (arr[j] % 2!= 0) {
            min = arr[j];
            break;
        }
    }
    double result;
    if (max!= -1 && min!= -1)
        result = (double)max / min;
    else
        result = -1;
    return result;
}