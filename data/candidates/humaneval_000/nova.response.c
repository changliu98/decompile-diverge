int func0(float arr[], int n, float x) {
    int i, j, flag;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (fabs(arr[i] - arr[j]) > x) {
                flag = 1;
                break;
            } else
                flag = 0;
        }
    }
    return flag;
}