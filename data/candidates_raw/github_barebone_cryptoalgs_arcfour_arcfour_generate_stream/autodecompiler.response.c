void arcfour_generate_stream(char state[], char out[], size_t len) {
    int i = 0, j = 0, t;
    size_t k;
    char temp;

    for(k = 0; k < len; k++) {
        i = (i + 1) % 256;
        j = (j + state[i]) % 256;
        temp = state[i];
        state[i] = state[j];
        state[j] = temp;

        t = (state[i] + state[j]) % 256;
        out[k] = state[t];
    }
}