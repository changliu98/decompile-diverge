void func0(float *array, int length, float *out) {
    float max_diff = 0.0f;
    
    // Initialize out[0] and out[1] with the first two elements
    out[0] = array[0];
    out[1] = array[1];
    
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            // Calculate absolute difference using fabsf
            float diff = fabsf(array[i] - array[j]);
            
            if (max_diff < diff) {
                max_diff = diff;
                out[0] = array[i];
                out[1] = array[j];
            }
        }
    }
    
    // Ensure out[0] is greater than out[1]
    if (out[0] < out[1]) {
        float temp = out[0];
        out[0] = out[1];
        out[1] = temp;
    }
}