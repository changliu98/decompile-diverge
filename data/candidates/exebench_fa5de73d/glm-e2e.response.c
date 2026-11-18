void QuaternionMult(Quaternion *out, const Quaternion *q1, const Quaternion *q2) {
    // w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z
    out->w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;

    // x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y
    out->x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;

    // y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x
    out->y = q1->w * q2->y - q1->x * q2->z + q1->y * q2->w + q1->z * q2->x;

    // z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w
    out->z = q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w;
}