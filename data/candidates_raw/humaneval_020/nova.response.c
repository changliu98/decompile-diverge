void func0(float *v, int n, float *minmax) {
    int i, j;
    float aux;
    float min, max;
    min = max = v[0];
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            aux = fabs(v[i] - v[j]);
            if (aux > max) {
                max = aux;
                minmax[0] = v[i];
                minmax[1] = v[j];
            }
        }
    }
    if (minmax[0] > minmax[1]) {
        aux = minmax[0];
        minmax[0] = minmax[1];
        minmax[1] = aux;
    }
}