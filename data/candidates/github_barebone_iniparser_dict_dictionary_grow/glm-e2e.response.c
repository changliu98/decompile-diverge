int dictionary_grow(struct dictionary *d) {
    void *new_keys;
    void *new_values;
    unsigned *new_hashes;
    int ret;

    // Allocate new arrays with double the capacity
    new_keys = calloc(d->size * 2, 8);
    new_values = calloc(d->size * 2, 8);
    new_hashes = calloc(d->size * 2, 4);

    // Check for allocation failures
    if (!new_keys || !new_values || !new_hashes) {
        if (new_keys)
            free(new_keys);
        if (new_values)
            free(new_values);
        if (new_hashes)
            free(new_hashes);
        ret = -1;
    } else {
        // Copy old data to the newly allocated arrays
        memcpy(new_keys, d->keys, d->size * 8);
        memcpy(new_values, d->values, d->size * 8);
        memcpy(new_hashes, d->hashes, d->size * 4);

        // Free old arrays
        free(d->keys);
        free(d->values);
        free(d->hashes);

        // Update dictionary struct with new capacity and arrays
        d->size *= 2;
        d->keys = new_keys;
        d->values = new_values;
        d->hashes = new_hashes;
        
        ret = 0;
    }

    return ret;
}