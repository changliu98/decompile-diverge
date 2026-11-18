void __cdecl rsQuat_preMult(float *q, float *postQuat)
{
    // Store original q components since q will be overwritten
    float qx = q[0];
    float qy = q[1];
    float qz = q[2];
    float qw = q[3];

    float px = postQuat[0];
    float py = postQuat[1];
    float pz = postQuat[2];
    float pw = postQuat[3];

    // q = postQuat * q (Hamilton product)
    q[0] = (pw * qx) + (px * qw) + (py * qz) - (pz * qy);
    q[1] = (pw * qy) - (px * qz) + (py * qw) + (pz * qx);
    q[2] = (pw * qz) + (px * qy) - (py * qx) + (pz * qw);
    q[3] = (pw * qw) - (px * qx) - (py * qy) - (pz * qz);
}