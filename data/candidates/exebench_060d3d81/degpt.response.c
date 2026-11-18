void quatmul(double *result, double *left, double *right)
{
    // r[0] = scalar part of quaternion product
    result[0] = -left[3] * right[3] - left[2] * right[2] + *left * *right - left[1] * right[1];
    // r[1] = x component of quaternion product
    result[1] = -left[3] * right[2] + left[2] * right[3] + left[1] * *right + *left * right[1];
    // r[2] = y component of quaternion product
    result[2] = -left[1] * right[3] + left[3] * right[1] + left[2] * *right + *left * right[2];
    // r[3] = z component of quaternion product
    result[3] = -left[2] * right[1] + left[1] * right[2] + left[3] * *right + *left * right[3];
}