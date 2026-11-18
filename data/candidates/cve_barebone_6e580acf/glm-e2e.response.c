struct Window* xf_Pointer_get_window(struct xfPointer* pointer) {
    if (pointer == NULL) {
        return NULL;
    }

    if (pointer->is_active != 0) {
        if (pointer->window == NULL) {
            return NULL;
        }
        return pointer->window->child;
    } else {
        if (pointer->screen == NULL) {
            return NULL;
        }
        return pointer->screen->root_window;
    }
}