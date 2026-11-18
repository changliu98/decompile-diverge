void crossp(double Q[3][3], double v[3], double w[3]) {
    Q[0][0] = v[1] * w[2] - v[2] * w[1];
    Q[0][1] = v[2] * w[0] - v[0] * w[2];
    Q[0][2] = v[0] * w[1] - v[1] * w[0];
}