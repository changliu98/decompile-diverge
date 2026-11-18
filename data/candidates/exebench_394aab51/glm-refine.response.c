void __cdecl rsQuat_postMult(float *q, const float *preQuat)
{
    // Cache the original components of q to prevent aliasing issues
    // when we overwrite q[0]..q[3] during the calculations.
    float tempx = q[0];
    float tempy = q[1];
    float tempz = q[2];
    float tempw = q[3];

    // Extract preQuat components for readability
    float px = preQuat[0];
    float py = preQuat[1];
    float pz = preQuat[2];
    float pw = preQuat[3];

    // Perform standard quaternion multiplication: q = q * preQuat
    q[0] = (pw * tempx) + (tempw * px) + (tempy * pz) - (tempz * py);
    q[1] = (pw * tempy) + (tempw * py) + (tempz * px) - (tempx * pz);
    q[2] = (pw * tempz) + (tempw * pz) + (tempx * py) - (tempy * px);
    q[3] = (pw * tempw) - (tempx * px) - (tempy * py) - (tempz * pz);
}