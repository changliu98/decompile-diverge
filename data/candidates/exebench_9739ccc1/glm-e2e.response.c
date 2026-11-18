void set_stimulus(unsigned char *state, const char *stimulus) {
    while (*stimulus != '\0') {
        if (*stimulus >= '0' && *stimulus <= '7') {
            *state &= ~(1 << (*stimulus - '0'));
        }
        stimulus++;
    }
}