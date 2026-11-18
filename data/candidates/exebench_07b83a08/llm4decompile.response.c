void Mat4_Translate( Mat4* m, const Vec3* v )
{
 m->m14 += m->m1 * v->x + m->m5 * v->y + m->m9 * v->z;
 m->m15 += m->m2 * v->x + m->m6 * v->y + m->m10 * v->z;
 m->m16 += m->m3 * v->x + m->m7 * v->y + m->m11 * v->z;
}