int dictionary_grow(dictionary *d)
{
    char **new_key = (char * *)(calloc((2 * d->size), sizeof(char *)));
    char **new_val = (char * *)(calloc((2 * d->size), sizeof(char *)));
    unsigned int *new_hash = (unsigned int *)(calloc((2 * d->size), sizeof(unsigned int)));
    if (new_key == NULL || new_val == NULL || new_hash == NULL)
    {
        if (new_key != NULL)
            free(new_key);
        if (new_val != NULL)
            free(new_val);
        if (new_hash != NULL)
            free(new_hash);
        return -1;
    }
    memcpy(new_key, d->key, d->size * sizeof(char *));
    memcpy(new_val, d->val, d->size * sizeof(char *));
    memcpy(new_hash, d->hash, d->size * sizeof(unsigned int));
    free(d->key);
    free(d->val);
    free(d->hash);
    d->key = new_key;
    d->val = new_val;
    d->hash = new_hash;
    d->size *= 2;
    return 0;
}