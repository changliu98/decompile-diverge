int func0(char *s, size_t len, int is_first, struct state *state) {
    int ret;
    int is_valid;
    int is_accepting;
    char *p;
    char *q;
    size_t i;

    is_valid = 0;
    is_accepting = 0;

    do {
        is_valid = 0;
        is_accepting = 0;

        if (len == 0) {
            is_valid = 1;
        }

        if (state->type == STATE_TYPE_FINAL) {
            is_accepting = 1;
        }

        if (is_accepting && is_first) {
            is_valid = 1;
        }

        if (is_accepting && state->type!= STATE_TYPE_FINAL) {
            is_valid = 1;
        }

        if (is_valid) {
            state->is_valid = 1;
        }

        if (is_valid && is_accepting) {
            is_valid = 1;
        }

        if (is_valid && state->type == STATE_TYPE_FINAL) {
            is_valid = 1;
        }

        if (is_valid && state->type == STATE_TYPE_FINAL) {
            is_valid = 1;
        }

        if (is_valid && state->type == STATE_TYPE_FINAL) {
            is_valid = 1;
        }

        if (is_valid && state->type == STATE_TYPE_FINAL) {
            is_valid = 1;
        }

        if (is_valid && state->type == STATE_TYPE_FINAL) {
            is_valid = 1;
        }

        if (is_valid && state->type == STATE_TYPE_FINAL) {
            is_valid = 1;
        }

        if (is_valid && state->type == STATE_TYPE_FINAL) {
            is_valid = 1;