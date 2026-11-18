void squeeze(struct State *state) {
    uint32_t sum = 0;
    int i;

    // First pass
    for (i = 0; i < 31; i++) {
        sum += state->arr[i];
        state->arr[i] = sum & 0xff;
        sum >>= 8;
    }

    sum += state->carry;
    state->carry = sum & 0x7f;
    sum = (sum >> 7) * 0x13;

    // Second pass
    for (i = 0; i < 31; i++) {
        sum += state->arr[i];
        state->arr[i] = sum & 0xff;
        sum >>= 8;
    }

    sum += state->carry;
    state->carry = sum;
}