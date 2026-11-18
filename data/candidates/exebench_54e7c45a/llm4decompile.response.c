int matMultMV(Matrix m, Vector v, Vector r) {
    double r0 = m.m[0] * v.v[0] + m.m[1] * v.v[1] + m.m[2] * v.v[2] + m.m[3] * v.v[3];
    double r1 = m.m[4] * v.v[0] + m.m[5] * v.v[1] + m.m[6] * v.v[2] + m.m[7] * v.v[3];
    double r2 = m.m[8] * v.v[0] + m.m[9] * v.v[1] + m.m[10] * v.v[2] + m.m[11] * v.v[3];
    double r3 = m.m[12] * v.v[0] + m.m[13] * v.v[1] + m.m[14] * v.v[2] + m.m[15] * v.v[3];

    r.v[0] = r0;
    r.v[1] = r1;
    r.v[2] = r2;
    r.v[3] = r3;

    return 0;
}