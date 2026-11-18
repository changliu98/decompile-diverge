int func0(unsigned int *out, const unsigned int len, const float min,
              const float max, unsigned int *state) {
    unsigned int i;
    float r;

    for (i = 0; i < len; i++) {
        r = (float)rand() / (float)RAND_MAX;
        out[i] = (unsigned int)(2.0f * (r - 0.5f));
    }

    return 1;
}