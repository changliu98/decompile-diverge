void vec3CrossProduct(float *vec, float *lhs, float *rhs)
{
    vec[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    vec[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    vec[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
}