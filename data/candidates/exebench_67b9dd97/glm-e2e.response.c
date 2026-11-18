float v_inner(float* a, float* b, int n) {
    int i = 0;
    float sum = 0.0f;
    
    while (i < n) {
        sum += a[i] * b[i];
        i++;
    }
    
    return sum;
}