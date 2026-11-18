void rsQuat_postMult(Quat *q1, const Quat *q2) {
    float x1 = q1->x;
    float y1 = q1->y;
    float z1 = q1->z;
    float w1 = q1->w;

    // q1 = q1 * q2
    q1->x = (w1 * q2->x) + (x1 * q2->w) + (y1 * q2->z) - (z1 * q2->y);
    q1->y = (w1 * q2->y) - (x1 * q2->z) + (y1 * q2->w) + (z1 * q2->x);
    q1->z = (w1 * q2->z) + (x1 * q2->y) - (y1 * q2->x) + (z1 * q2->w);
    q1->w = (w1 * q2->w) - (x1 * q2->x) - (y1 * q2->y) - (z1 * q2->z);
}