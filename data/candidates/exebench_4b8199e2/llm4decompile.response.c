double randlc(double *x, double a)
{







    double a1, x1, a2, x2, z, r, t1, t2, t3, t4, t23, t46, r23, r46;
    int i;

    a1 = (int)((a * 4096.0) + a);
    x1 = (int)((*x * 4096.0) + *x);
    a2 = (int)(a * 4096.0);
    x2 = (int)(*x * 4096.0);
    t1 = (a1 * x2) + (a2 * x1);
    t2 = (int)(t1 * 4096.0);
    t3 = t2 + (t1 - t2);
    t4 = t3 * 4096.0;
    t46 = t4 + t3;
    r23 = (t23 = t3 * 4096.0) + (t2 - t23);
    r46 = (t46 * 67108864.0) + (t4 - t46);
    *x = (r46 * 4096.0) + r23;
    z = *x * 2.32830643653869628906e-10;
    return (z);
}