float *func0(float *coeff, int degree, int *newDegree) {
    float *newCoeff = (float *)malloc(sizeof(float) * (degree + 1));
    *newDegree = 0;
    for (int i = 0; i < degree + 1; i++) {
        if (coeff[i] > 0) {
            newCoeff[(*newDegree)++] = coeff[i];
        }
    }
    return newCoeff;
}