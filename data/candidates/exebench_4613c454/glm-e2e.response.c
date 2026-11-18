void cquat_scale(struct quat *out, double scale, const struct quat *in) {
    out->w = in->w * scale;
    out->x = in->x * scale;
    out->y = in->y * scale;
    out->z = in->z * scale;
}