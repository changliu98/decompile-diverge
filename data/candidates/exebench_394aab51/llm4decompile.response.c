void rsQuat_postMult(float *dstQuat, const float *srcQuat)
{
    float x, y, z, w;
    float x1, y1, z1, w1;

    x = dstQuat[0];
    y = dstQuat[1];
    z = dstQuat[2];
    w = dstQuat[3];

    x1 = srcQuat[0];
    y1 = srcQuat[1];
    z1 = srcQuat[2];
    w1 = srcQuat[3];

    dstQuat[0] = w * x1 + x * w1 - y * z1 + z * y1;
    dstQuat[1] = w * y1 + y * w1 + z * x1 - x * z1;
    dstQuat[2] = w * z1 + z * w1 + x * y1 - y * x1;
    dstQuat[3] = w * w1 - x * x1 - y * y1 - z * z1;
}