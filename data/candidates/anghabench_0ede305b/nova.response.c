static int fons__decutf8(struct state *s, int *time, int in) {
    int next;
    int t = delta[s->pos][in];
    if (s->pos!= FIN)
        next = (t << 6) | (in & 0x3f);
    else
        next = (in & (FSM_IN_MASK));
    *time = next;
    s->pos = FSM_T_TABLE[s->pos + t];
    return s->pos;
}