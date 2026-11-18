void SCE_Quaternion_MulCopyInv (SCE_TQuaternion a, SCE_TQuaternion b)
{
    float w, x, y, z;
    w = a[0]; x = a[1]; y = a[2]; z = a[3];
    a[0] = -w*b[0] + b[3]*x + b[1]*y - b[2]*z;
    a[1] = -x*b[0] + b[3]*y + b[2]*w - b[1]*z;
    a[2] = -y*b[0] + b[3]*z + b[0]*x - b[2]*w;
    a[3] = -z*b[0] + b[3]*w - b[1]*x - b[2]*y;
}