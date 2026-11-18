void __cdecl xformMultiply(Matrix2x3 *t, const Matrix2x3 *s)
{
    // Store the original rows of 't' because 't' is modified in-place
    // and later calculations depend on the original 't' values.
    float t0 = t->m0;
    float t1 = t->m1;
    float t2 = t->m2;
    float t3 = t->m3;
    float t4 = t->m4;
    float t5 = t->m5;

    // Row 0 of the resulting matrix
    t->m0 = (t0 * s->m0) + (t1 * s->m2);
    t->m1 = (t0 * s->m1) + (t1 * s->m3);
    t->m4 = (t4 * s->m0) + (t5 * s->m2) + s->m4;

    // Row 1 of the resulting matrix
    t->m2 = (t2 * s->m0) + (t3 * s->m2);
    t->m3 = (t2 * s->m1) + (t3 * s->m3);
    t->m5 = (t4 * s->m1) + (t5 * s->m3) + s->m5;
}