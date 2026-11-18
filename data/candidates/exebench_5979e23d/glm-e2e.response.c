void vscale(struct Vec3 *out, const struct Vec3 *in, float scale) {
    out->x = in->x * scale;
    out->y = in->y * scale;
    out->z = in->z * scale;
}