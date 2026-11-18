void geom_matinv2d(struct matrix *m)
{
 double det = 1 / (m->a * m->d - m->b * m->c);
 double temp = m->a;
 m->a = m->d * det;
 m->b = m->b * -det;
 m->c = m->c * -det;
 m->d = temp * det;
}