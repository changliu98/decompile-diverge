struct alloc_block *get_register(int name, int copy) {
    struct alloc_block *reg;

    get_yank_register(name, 0);

    reg = alloc(0x18);
    if (reg == NULL) {
        return NULL;
    }

    // Copy 24 bytes (3 fields of 8 bytes each) from *y_current to *reg
    reg->array = y_current->array;
    reg->count = y_current->count;
    reg->unknown = y_current->unknown;

    if (copy != 0) {
        if (reg->count == 0) {
            reg->array = NULL;
        } else {
            reg->array = alloc(reg->count * 8);
        }

        if (reg->array != NULL) {
            for (int i = 0; i < reg->count; i++) {
                reg->array[i] = vim_strsave(y_current->array[i]);
            }
        }
    } else {
        y_current->array = NULL;
    }

    return reg;
}