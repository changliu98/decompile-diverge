float catmull_rom_val(int n, float x[], float y[], float t, float w[]) {
    int i, j, k;
    float z, u, v, p, q;
    k = 0;
    for (i = 0; i < n - 2; i++) {
        if (t > x[i + 1])
            k = i;
        else
            break;
    }
    z = (t - x[k]) / (x[k + 1] - x[k]);
    u = 1 - z;
    v = z;
    p = v * v;
    q = u * u;
    return (w[k] * p * u + w[k + 1] * q * v + w[k + 2] * p * v +
            w[k + 3] * q * u);
}