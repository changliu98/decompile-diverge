void arcfour_generate_stream(unsigned char *state,
                             unsigned char *out,
                             size_t len)
{
    int i = 0;
    int j = 0;
    size_t k = 0;
    unsigned char t = 0;

    for (k = 0; k < len; k++) {
        i = (i + 1) % 256;
        j = (j + state[i]) % 256;
        t = state[i];
        state[i] = state[j];
        state[j] = t;
        out[k] = state[(state[i] + state[j]) % 256];
    }
}