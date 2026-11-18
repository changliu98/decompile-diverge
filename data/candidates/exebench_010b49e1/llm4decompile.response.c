float vec4DotProduct(const Vec4 *lhs, const Vec4 *rhs) {
    return lhs->x * rhs->x + lhs->y * rhs->y + lhs->z * rhs->z + lhs->w * rhs->w;
}