void cquat_add(double *result, double *left, double *right)
{
    // Add the scalar parts of quaternions a and b, store result in q
    *result = *left + *right;
    // Add the x components of quaternions a and b, store result in q
    result[1] = left[1] + right[1];
    // Add the y components of quaternions a and b, store result in q
    result[2] = left[2] + right[2];
    // Add the z components of quaternions a and b, store result in q
    result[3] = left[3] + right[3];
}