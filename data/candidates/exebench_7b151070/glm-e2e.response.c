void Mat4_RotateQuaternion(Mat4 *out, const Quat *q) {
    float q0 = -q->x;
    float q1 = -q->y;
    float q2 = -q->z;
    float q3 = q->w;

    float v0 = q3 * out->m[0][0] + q0 * out->m[1][0] + q1 * out->m[2][0] - q2 * out->m[3][0];
    float v1 = q3 * out->m[0][1] + q0 * out->m[1][1] + q1 * out->m[2][1] - q2 * out->m[3][1];
    float v2 = q3 * out->m[0][2] + q0 * out->m[1][2] + q1 * out->m[2][2] - q2 * out->m[3][2];
    float v3 = q3 * out->m[0][3] - q0 * out->m[1][3] - q1 * out->m[2][3] - q2 * out->m[3][3];

    out->m[0][0] = v3 * q3 + v0 * q0 + v1 * q1 - v2 * q2;
    out->m[0][1] = v3 * q1 + v0 * q2 - v1 * q0 - v2 * q3;
    out->m[0][2] = v3 * q2 - v0 * q1 + v1 * q0 - v2 * q3;
    out->m[0][3] = v3 * q3 - v0 * q0 - v1 * q1 - v2 * q2;
    out->m[0][3] = 0.0f;

    float v4 = q3 * out->m[0][0] + q0 * out->m[1][0] + q1 * out->m[2][0] - q2 * out->m[3][0];
    float v5 = q3 * out->m[0][1] + q0 * out->m[1][1] + q1 * out->m[2][1] - q2 * out->m[3][1];
    float v6 = q3 * out->m[0][2] + q0 * out->m[1][2] + q1 * out->m[2][2] - q2 * out->m[3][2];
    float v7 = q3 * out->m[0][3] - q0 * out->m[1][3] - q1 * out->m[2][3] - q2 * out->m[3][3];

    out->m[1][0] = v7 * q3 + v4 * q0 + v5 * q1 - v6 * q2;
    out->m[1][1] = v7 * q1 + v4 * q2 - v5 * q0 - v6 * q3;
    out->m[1][2] = v7 * q2 - v4 * q1 + v5 * q0 - v6 * q3;
    out->m[1][3] = v7 * q3 - v4 * q0 - v5 * q1 - v6 * q2;
    out->m[1][3] = 0.0f;

    float v8 = q3 * out->m[0][0] + q0 * out->m[1][0] + q1 * out->m[2][0] - q2 * out->m[3][0];
    float v9 = q3 * out->m[0][1] + q0 * out->m[1][1] + q1 * out->m[2][1] - q2 * out->m[3][1];
    float v10 = q3 * out->m[0][2] + q0 * out->m[1][2] + q1 * out->m[2][2] - q2 * out->m[3][2];
    float v11 = q3 * out->m[0][3] - q0 * out->m[1][3] - q1 * out->m[2][3] - q2 * out->m[3][3];

    out->m[2][0] = v11 * q3 + v8 * q0 + v9 * q1 - v10 * q2;
    out->m[2][1] = v11 * q1 + v8 * q2 - v9 * q0 - v10 * q3;
    out->m[2][2] = v11 * q2 - v8 * q1 + v9 * q0 - v10 * q3;
    out->m[2][3] = v11 * q3 - v8 * q0 - v9 * q1 - v10 * q2;
    out->m[2][3] = 0.0f;
}