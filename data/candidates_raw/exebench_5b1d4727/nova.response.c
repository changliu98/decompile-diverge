float func0(float *v1, float *v2, long dim) {
    float result = 0.0;
    for (int i = 0; i < dim; i++)
        result += v1[i] * v2[i];
    return result;
}