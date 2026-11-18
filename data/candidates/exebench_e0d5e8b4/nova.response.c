void dstsub4(int N, float *v) {
    float alpha, beta, gamma, delta;
    int i;

    alpha = 0.5;
    beta = 0.75;
    gamma = 0.5;
    delta = 0.25;

    i = N >> 1;
    if (i == 2) {
        float a, b, c, d;
        a = alpha * v[0] + beta * v[2];
        b = gamma * v[0] + delta * v[2];
        v[2] = a * v[1] + b * v[3];
        v[3] = b * v[1] + a * v[3];
    }
    v[i] = alpha * v[i] + beta * v[i + 2];
    v[i + 1] = gamma * v[i] + delta * v[i + 2];
}