int* func0(int *v, int n, int c, int *out_n) {
    int size;
    if (n > 0) {
        size = 2 * n - 1;
    } else {
        size = 0;
    }
    
    *out_n = size;
    int *out = (int *)malloc(size * sizeof(int));
    
    if (n > 0) {
        out[0] = v[0];
    }
    
    int i = 1;
    int j = 1;
    while (i < n) {
        out[j++] = c;
        out[j++] = v[i];
        i++;
    }
    
    return out;
}