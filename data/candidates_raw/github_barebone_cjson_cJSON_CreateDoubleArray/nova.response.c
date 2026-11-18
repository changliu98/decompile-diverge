struct poly *func0(double *coeffs, int n) {
    struct poly *p, *q, *r;
    int i;
    double x;
    char sign;

    if (n < 0 || coeffs == NULL)
        return NULL;

    p = newpoly();
    for (i = 0;; i++) {
        x = coeffs[i];
        sign = (x!= 0) && (i < n);
        if (!sign)
            break;
        q = newpoly();
        q->c = x;
        if (p == NULL) {
            p = q;
            continue;
        }
        if (i == 0)
            p->next = q;
        else
            insert(r, q);
        r = q;
    }
    if (p!= NULL && p->next!= NULL)
        p->next->prev = q;
    return p;
}