void update_gyro_matrix(ahrs_t *ahrs, double dcm[3][3])
{
    double kp, ki;
    double p, q, r;
    double ex, ey, ez;

    kp = ahrs->kp;
    ki = ahrs->ki;

    p = ahrs->p;
    q = ahrs->q;
    r = ahrs->r;

    ex = (1 + q + r - p) * (1 - q - r - p) * (1 + p * (q - r));
    ey = (1 + p + r - q) * (1 - p + r - q) * (1 + q * (p - r));
    ez = (1 + p + q - r) * (1 - p + q - r) * (1 + r * (p - q));

    double inv_dt = 1 / ((1 + p + q + r) * (1 - p - q - r) * (1 + p * p + q * q + r * r));

    dcm[0][0] = inv_dt * (1 + p * (-p + q + r)) * (1 + p * (-p + q + r) - q - r);
    dcm[0][1] = inv_dt * (1 + p + q) * (1 + p * (q - r) + q * r);
    dcm[0][2] = inv_dt * p * (1 + p * (q - r) + q * r);

    dcm[1][0] = inv_dt * (1 + p + q) * (1 + p * (q - r) + q * r);
    dcm[1][1] = inv_dt * (-1 + q * (-q + r)) * (1 + q * (-q + r) + p * p);
    dcm[1][2] = inv_dt * (-p) * (1 + p * (q - r) + q * r + p * p - 1);

    dcm[2][0] = inv_dt * (1 + q * (q - r) + p * p + p * q - p) * (1 + q * (q - r) + p * p + p * q - p);
    dcm[2][1] = inv_dt * (1 + q * (q - r) + p * p + p * q - p) * (1 + q * (q - r) + p * p + p * q - p + q * q - q);
    dcm[2][2] = inv_dt * (1 + q * (q - r) + p * p + p * q - p) * (1 + q * (q - r) + p * p + p * q - p + q * q - q + r * r - r);
}