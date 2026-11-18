float vectorDotProduct(int length, float *vectorA, float *vectorB) {
    float result = 0.0f;
    for (int i = 0; i < length; i++) {
        result += vectorA[i] * vectorB[i];
    }
    return result;
}