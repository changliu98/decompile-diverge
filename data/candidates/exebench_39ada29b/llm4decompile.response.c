void rsQuat_preMult(float *q, const float *postQuat)
{
    float w, x, y, z;
    float w1, x1, y1, z1;

    w1 = q[0];
    x1 = q[1];
    y1 = q[2];
    z1 = q[3];

    w = w1 * postQuat[0] - x1 * postQuat[1] - y1 * postQuat[2] - z1 * postQuat[3];
    x = w1 * postQuat[1] + x1 * postQuat[0] + y1 * postQuat[3] - z1 * postQuat[2];
    y = w1 * postQuat[2] - x1 * postQuat[3] + y1 * postQuat[0] + z1 * postQuat[1];
    z = w1 * postQuat[3] + x1 * postQuat[2] - y1 * postQuat[1] + z1 * postQuat[0];

    q[0] = w;
    q[1] = x;
    q[2] = y;
    q[3] = z;
}