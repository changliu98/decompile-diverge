void pa(float *v, float a, float b) {
    for (int i = 0; i < 6; i++) {
        v[0] = (v[0] + v[1] + v[2] - v[3]) * a;
        v[1] = (v[0] + v[1] - v[2] + v[3]) * a;
        v[2] = (v[0] - v[1] + v[2] + v[3]) * a;
        v[3] = (-v[0] + v[1] + v[2] + v[3]) / b;
    }
}