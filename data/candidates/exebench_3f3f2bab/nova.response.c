int sboxCHECK(float *v1, float *v2, int n) {
    int i, sboxCHECK = 1;

    if (v1 == NULL || v2 == NULL) {
        sboxCHECK = 1;
    } else {
        for (i = 0; i < n; i++) {
            if (v1[i] > v2[i]) {
                sboxCHECK = 0;
                break;
            }
        }
    }
    return sboxCHECK;
}