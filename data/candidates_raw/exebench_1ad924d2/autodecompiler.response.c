double jachatfldf(double x, double y, double z, double u, double v, double *f)
{
    int i;
    double d, a2, b2, c2, d2, e2, ab, de, c2pd2, Q, temp;
    a2 = x * x;
    b2 = y * y;
    c2 = z * z;
    d2 = u * u;
    e2 = v * v;
    c2pd2 = c2 + d2;
    ab = x * y;
    de = u * v;
    Q = z * (c2pd2 + e2);
    f[0] = -y * de + x * (c2 + e2);
    f[1] = y * c2pd2 + ab * de;
    f[2] = Q;
    f[3] = -z * (x * u + y * v);
    f[4] = u * (b2 + c2) + ab * de;
    f[5] = -ab * de + v * (a2 + c2);
    f[6] = f[3];
    f[7] = z * (a2 + b2 + c2);
    d = f[0] * x + f[1] * y + f[2] * z;
    for (i = 0; i < 9; ++i)
    {
        f[i] = f[i] / d;
    }
}