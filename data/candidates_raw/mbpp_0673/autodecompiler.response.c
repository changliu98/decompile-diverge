int combi(int *arr, int n) {
    int i;
    int ret = 0;

    for (i = 0; ; i++) {
        if (i >= n) break;
        ret = ret * 10 + arr[i];
    }

    return ret;
}