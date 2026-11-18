long rnd_between(long *state, long min, long max) {
    long range = max - min + 1;
    *state = (*state * 0x6255 + 0x3619) % range + min;
    return *state;
}