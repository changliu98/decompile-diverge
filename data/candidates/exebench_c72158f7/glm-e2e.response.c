double rnd(long *state) {
    *state = (*state * 0x6255 + 0x3619) % 0x10000;
    return (double)*state / 10000.0;
}