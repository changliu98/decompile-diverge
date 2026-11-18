static int FNEGQ(BIGNUM *r, const BIGNUM *a)
{
    r->neg = a->neg ^ 0x8000000000000000ULL;
    r->top = a->top;
    r->d = a->d;
    return 1;
}