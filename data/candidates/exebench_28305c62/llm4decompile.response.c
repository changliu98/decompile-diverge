float vec3DotProduct(const Vec3 *lhs, const Vec3 *rhs)
{
    return lhs->x * rhs->x + lhs->y * rhs->y + lhs->z * rhs->z;
}