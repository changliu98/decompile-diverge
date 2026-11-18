void rsQuat_preMult (SCE_TQuaternion a, SCE_TQuaternion b)
{
    float w, x, y, z;
    w = a[0]; x = a[1]; y = a[2]; z = a[3];
    a[0] = w*b[0] + x*b[3] + y*b[2] + z*(-b[1]);
    a[1] = w*b[1] + x*b[3] + y*b[0] + z*(-b[2]);
    a[2] = w*b[2] + x*b[3] + y*b[0] + z*(-b[1]);
    a[3] = w*b[3] + x*b[0] + y*b[1] + z*(-b[2]);
}