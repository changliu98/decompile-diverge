void* xf_Pointer_get_window(struct _X* arg) {
    void* ret = NULL;

    if (arg == NULL) {
        WLog_Print_dbg_tag("...", 3, 0xa0, "...", "...", "...");
        return NULL;
    }

    if (arg->flag != 0) {
        if (arg->other == NULL) {
            WLog_Print_dbg_tag("...", 3, 0xa7, "...", "...", "...");
            return NULL;
        }
        ret = ((struct _Y*)arg->other)->window;
    } else {
        if (arg->window == NULL) {
            WLog_Print_dbg_tag("...", 3, 0xb0, "...", "...", "...");
            return NULL;
        }
        ret = *(void**)arg->window;
    }

    return ret;
}