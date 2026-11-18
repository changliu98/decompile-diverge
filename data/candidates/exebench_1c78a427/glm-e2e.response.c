void cquat_to_matrix_t(const double *q, double *m) {
    double q0 = q[0];
    double q1 = q[1];
    double q2 = q[2];
    double q3 = q[3];

    // Row 0
    m[0] = 1.0 - 2.0 * (q2 * q2 + q1 * q1);
    m[1] = 2.0 * (q1 * q3 - q0 * q2);
    m[2] = 2.0 * (q1 * q2 + q0 * q3);

    // Row 1
    m[3] = 2.0 * (q1 * q3 + q0 * q2);
    m[4] = 1.0 - 2.0 * (q1 * q1 + q3 * q3);
    m[5] = 2.0 * (q2 * q3 - q0 * q1);

    // Row 2
    m[6] = 2.0 * (q1 * q2 - q0 * q3);
    m[7] = 2.0 * (q2 * q3 + q0 * q1);
    m[8] = 1.0 - 2.0 * (q0 * q0 + q3 * q3);
}