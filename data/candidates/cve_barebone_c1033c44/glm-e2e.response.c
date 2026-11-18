void* mrb_realloc(struct mrb_state* mrb, void* ptr, size_t len) {
    void* new_ptr;
    void* ret;

    new_ptr = mrb_realloc_simple(mrb, ptr, len);

    if (len == 0) {
        ret = new_ptr;
    } else {
        if (new_ptr == NULL) {
            mrb_free(mrb, ptr);
            // Clear bits 4 and 5, and set bit 4 (AND 0xef, OR 0x10)
            mrb->gc.generational = (mrb->gc.generational & 0xef) | 0x10;
            mrb_raise_nomemory(mrb);
        } else {
            // Clear bits 4 and 5 (AND 0xef, OR 0x0)
            mrb->gc.generational = (mrb->gc.generational & 0xef) | 0x0;
        }
        ret = new_ptr;
    }

    return ret;
}