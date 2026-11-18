int func0(float *v1, float *v2, int n) {
    int i, func0 = 1;

    if (v1 == NULL || v2 == NULL) {
        func0 = 1;
    } else {
        for (i = 0; i < n; i++) {
            if (v1[i] > v2[i]) {
                func0 = 0;
                break;
            }
        }
    }
    return func0;
}