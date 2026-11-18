float xCorrCoef(float* arr1, float* arr2, int length) {
    float sum_xy = 0.0f;
    float sum_y2 = 0.0f;
    
    for (int i = 0; i < length; i++) {
        sum_xy += arr1[i] * arr2[i];
        sum_y2 += arr2[i] * arr2[i];
    }
    
    if (sum_xy > 0.0f) {
        return (sum_xy * sum_xy) / sum_y2;
    } else {
        return 0.0f;
    }
}