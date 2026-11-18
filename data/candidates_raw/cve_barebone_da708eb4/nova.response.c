static struct symbol *func0(uchar op, struct forth_stack *st) {
    struct forth_stack *t;
    struct symbol *ret;
    int n;

    switch (op) {
    case 0x94:
        return &symbol_colon;
    }

    t = pop_frame(op, st);
    st = pop_frame(op, st);

    if (t->cell[2] & 0x30) {
        ret = &symbol_colon;
    } else if (t->cell[2] & 0x40) {
        ret = NULL;
    } else {
        if (st->compiled == NULL) {
            n = pop_int(op, st) + 0xe;
            st->compiled = (struct forth_stack *)malloc(n);
            memcpy(st->compiled, t, n);
        }
        ret = st->compiled;
    }

    return ret;
}