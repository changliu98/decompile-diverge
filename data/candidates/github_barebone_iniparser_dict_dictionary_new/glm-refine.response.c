dictionary *__cdecl dictionary_new(size_t size)
{
    dictionary *d;
    size_t actual_size;

    // Enforce a minimum dictionary capacity of 128
    actual_size = (size < 128) ? 128 : size;

    // Allocate the dictionary structure
    d = (dictionary *)calloc(1, sizeof(dictionary));
    if (d)
    {
        d->size = actual_size;
        d->val  = (char **)calloc(actual_size, sizeof(char *));
        d->key  = (char **)calloc(actual_size, sizeof(char *));
        d->hash = (unsigned int *)calloc(actual_size, sizeof(unsigned int));

        // Check if any of the internal arrays failed to allocate
        if (!d->val || !d->key || !d->hash)
        {
            // Safely free allocated memory before returning NULL
            free(d->key);
            free(d->val);
            free(d->hash);
            free(d);
            return NULL;
        }
    }
    
    return d;
}