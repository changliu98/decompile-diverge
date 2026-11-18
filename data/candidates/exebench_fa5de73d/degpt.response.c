void QuaternionMult(float *result, float *q1, float *q2)
{
    // Calculate the scalar part (w) of the resulting quaternion
    // w = w1*w2 - (x1*x2 + y1*y2 + z1*z2)
    result[0] = -q2[3] * q1[3] - q2[2] * q1[2] + *q2 * *q1 - q2[1] * q1[1];

    // Calculate the x component of the resulting quaternion
    // x = w1*x2 + x1*w2 + y1*z2 - z1*y2
    result[1] = q2[3] * q1[2] - q2[2] * q1[3] + q2[1] * *q1 + *q2 * q1[1];

    // Calculate the y component of the resulting quaternion
    // y = w1*y2 - x1*z2 + y1*w2 + z1*x2
    result[2] = -q2[3] * q1[1] - q2[2] * *q1 + *q2 * q1[2] + q2[1] * q1[3];

    // Calculate the z component of the resulting quaternion
    // z = w1*z2 + x1*y2 - y1*x2 + z1*w2
    result[3] = q2[3] * *q1 - q2[2] * q1[1] + *q2 * q1[3] - q2[1] * q1[2];
}