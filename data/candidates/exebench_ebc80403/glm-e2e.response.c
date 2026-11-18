void Vec3MultValue(const struct Vec3 *in, double value, struct Vec3 *out) {
    out->x = in->x * value;
    out->y = in->y * value;
    out->z = in->z * value;
}