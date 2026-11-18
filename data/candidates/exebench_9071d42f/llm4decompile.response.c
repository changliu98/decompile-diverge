void cmul(complex *a, complex *b)
{
    double rr, ii;

    rr = a->r * b->r - a->i * b->i;
    ii = a->r * b->i + a->i * b->r;
    a->r = rr;
    a->i = ii;
}