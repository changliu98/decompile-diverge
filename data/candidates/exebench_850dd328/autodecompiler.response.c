void cquat_set(Quaternion q, Quaternion a, Quaternion b)
{
    q[0] = a[0] + b[0];
    q[1] = a[1] + b[1];
    q[2] = a[2] + b[2];
    q[3] = a[3] + b[3];
}