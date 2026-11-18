int func0(float *a, float *b, int n) {
    int i;
    int flag = 1;
    if (a == NULL || b == NULL) {
        flag = 1;
    } else {
        for (i = 0; i < n; i++) {
            if (a[i] > b[i]) {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}