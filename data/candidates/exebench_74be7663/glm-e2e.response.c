void mlPointSub(float *p1, float *p2) {
    for (int i = 0; i < 3; i++) {
        p1[i] -= p2[i];
    }
}