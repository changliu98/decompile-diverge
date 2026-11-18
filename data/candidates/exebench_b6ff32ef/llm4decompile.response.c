void xformMultiply(Transform *t, const Transform *s)
{
    float x = t->m00 * s->m00 + t->m01 * s->m10;
    float y = t->m00 * s->m01 + t->m01 * s->m11;
    float z = t->m00 * s->m02 + t->m01 * s->m12 + s->m20;

    float x2 = t->m02 * s->m00 + t->m12 * s->m10;
    float y2 = t->m02 * s->m01 + t->m12 * s->m11;
    float z2 = t->m02 * s->m02 + t->m12 * s->m12 + s->m21;

    t->m00 = x;
    t->m01 = y;
    t->m02 = z;

    t->m12 = x2;
    t->m10 = y2;
    t->m11 = z2;
}