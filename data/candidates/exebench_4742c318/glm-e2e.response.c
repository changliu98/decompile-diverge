float mayorDif(float arr[]) {
    float diff = 0.0f;
    float max_diff = 0.0f;
    int i = 0;
    
    while (arr[i + 1] != 0.0f) {
        diff = arr[i] - arr[i + 1];
        diff = fabsf(diff);
        
        if (diff > max_diff) {
            max_diff = diff;
        }
        i++;
    }
    
    return max_diff;
}