struct dictionary *dictionary_new(size_t size) {
    if (size < 0x80) {
        size = 0x80;
    }
    
    struct dictionary *d = calloc(1, 0x28);
    if (d != NULL) {
        d->size = size;
        d->keys = calloc(size, 8);
        d->values = calloc(size, 8);
        d->hashes = calloc(size, 4);
        
        // If any of the allocations failed, clean up and return NULL
        if (d->size == 0 || d->keys == NULL || d->hashes == NULL) {
            free(d->keys); // free(NULL) is safe if keys allocation failed
            free(d->values);
            free(d->hashes);
            free(d);
            d = NULL;
        }
    }
    
    return d;
}