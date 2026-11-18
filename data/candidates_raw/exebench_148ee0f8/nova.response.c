void func0(float *out, const struct Quaternion *q) {
    float norm = q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z;
    out[0] = -(q->y * q->y + q->z * q->z) / norm;
    out[1] = (2.0f * q->x * q->y / norm);
    out[2] = (2.0f * q->z * q->x / norm);
    out[3] = -(q->y * q->z * 2.0f / norm);
}