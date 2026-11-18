void endrun(struct State *state) {
    state->remaining--;
    literal(state, state->byte);
    
    if (state->remaining >= 0x43) {
        encodelen(state, state->remaining - 0x43, 0x115, 4);
    } else if (state->remaining >= 0x23) {
        encodelen(state, state->remaining - 0x23, 0x111, 3);
    } else if (state->remaining >= 0x13) {
        encodelen(state, state->remaining - 0x13, 0x10d, 2);
    } else if (state->remaining >= 0xb) {
        encodelen(state, state->remaining - 0xb, 0x109, 1);
    } else if (state->remaining >= 0x3) {
        encodelen(state, state->remaining - 0x3, 0x101, 0);
    } else {
        while (state->remaining != 0) {
            state->remaining--;
            literal(state, state->byte);
        }
    }
}