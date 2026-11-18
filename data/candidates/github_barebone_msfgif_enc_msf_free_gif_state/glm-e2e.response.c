void msf_free_gif_state(struct GifState *state) {
    if (state->ptr_10 != NULL) {
        free(state->ptr_10);
    }
    if (state->ptr_30 != NULL) {
        free(state->ptr_30);
    }
    if (state->ptr_50 != NULL) {
        free(state->ptr_50);
    }
    if (state->ptr_58 != NULL) {
        free(state->ptr_58);
    }
    if (state->ptr_60 != NULL) {
        free(state->ptr_60);
    }

    struct Node *curr = state->list;
    while (curr != NULL) {
        struct Node *next = curr->next;
        free(curr);
        curr = next;
    }
    
    state->list = NULL;
}