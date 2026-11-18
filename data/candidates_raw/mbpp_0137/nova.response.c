double func0(int *arr, int size) {
    int i, count = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] == 0)
            count++;
        else
            continue;
    }
    double res = (double)count / size * 100;
    res = round(res / 10) * 10;
    return res;
}