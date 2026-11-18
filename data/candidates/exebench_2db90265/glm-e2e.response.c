int inicializa(struct Pair *p, int n, int *out1, int *out2) {
    int ret = 0;
    
    if (n % 2 != 0) {
        *out1 = p->a;
        *out2 = p->a;
        ret = 1;
    } else {
        ret = 2;
        if (p->a < p->b) {
            *out1 = p->a;
            *out2 = p->b;
        } else {
            *out1 = p->b;
            *out2 = p->a;
        }
    }
    
    return ret;
}