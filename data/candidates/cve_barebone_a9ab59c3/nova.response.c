int dns_packet_is_reply_for(struct state *s, FILE *file) {
    int c;

    assert(s!= NULL || errno == EINVAL);
    assert(file!= NULL || errno == EINVAL);

    if (is_new_state(state(s)) & 0x8000) {
        c = 0;
    } else {
        c = state_to_char(s);
        if (c > 0) {
            c = 0;
        } else {
            if (s->current->n == 1) {
                c = 0;
            } else {
                c = write_char(s->current->edges[0].to_state, file);
            }
        }
    }

    return c;
}