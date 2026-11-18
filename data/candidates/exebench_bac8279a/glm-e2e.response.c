int bppm_symbol(struct probs *p) {
    char c;
    
    if (p->p0 > 0.5) {
        c = '.';
    } else if (p->p1 > 0.5) {
        c = '(';
    } else if (p->p2 > 0.5) {
        c = ')';
    } else if (p->p1 + p->p2 > p->p0) {
        if (p->p1 / (p->p1 + p->p2) > 0.5) {
            c = '{';
        } else if (p->p2 / (p->p1 + p->p2) > 0.5) {
            c = '}';
        } else {
            c = '|';
        }
    } else if (p->p0 > p->p1 + p->p2) {
        c = ',';
    } else {
        c = ':';
    }
    
    return (int8_t)c;
}