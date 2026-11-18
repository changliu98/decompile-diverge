void xf_AppWindowDestroyImage(struct _state *state) {
    if (state->cache!= NULL) {
        state->cache->next->prev = NULL;
        free(state->cache);
    }
    state->cache = NULL;
}