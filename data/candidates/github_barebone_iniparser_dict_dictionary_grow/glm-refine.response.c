int __cdecl dictionary_grow(dictionary *d)
{
    size_t new_size = d->size * 2;

    // Allocate new arrays for values, keys, and hashes
    char **new_val = (char **)calloc(new_size, sizeof(char *));
    char **new_key = (char **)calloc(new_size, sizeof(char *));
    unsigned int *new_hash = (unsigned int *)calloc(new_size, sizeof(unsigned int));

    // Check if all allocations succeeded
    if (new_val && new_key && new_hash)
    {
        // Copy existing data to the new arrays
        memcpy(new_val, d->val, d->size * sizeof(char *));
        memcpy(new_key, d->key, d->size * sizeof(char *));
        memcpy(new_hash, d->hash, d->size * sizeof(unsigned int));

        // Free old arrays
        free(d->val);
        free(d->key);
        free(d->hash);

        // Update dictionary metadata and pointers
        d->size = new_size;
        d->val = new_val;
        d->key = new_key;
        d->hash = new_hash;

        return 0;
    }
    else
    {
        // Clean up any partially allocated arrays on failure
        if (new_val)
            free(new_val);
        if (new_key)
            free(new_key);
        if (new_hash)
            free(new_hash);

        return -1;
    }
}