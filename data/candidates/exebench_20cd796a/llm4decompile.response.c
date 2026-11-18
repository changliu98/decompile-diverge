void cquat_add(struct cquaternion *q, struct cquaternion *a, struct cquaternion *b)
{
    q->w = a->w + b->w;
    q->x = a->x + b->x;
    q->y = a->y + b->y;
    q->z = a->z + b->z;
}