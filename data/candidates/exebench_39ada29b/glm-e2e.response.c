void rsQuat_preMult(rsQuat *q, const rsQuat *r) {
    float q0 = q->x;
    float q1 = q->y;
    float q2 = q->z;
    float q3 = q->w;

    q->x = q3 * r->w + q0 * r->x + q1 * r->z - q2 * r->y;
    q->y = q3 * r->w + q1 * r->y + q2 * r->x - q0 * r->z;
    q->z = q3 * r->w + q2 * r->z + q0 * r->y - q1 * r->x;
    q->w = q3 * r->w - q0 * r->x - q1 * r->y - q2 * r->z;
}