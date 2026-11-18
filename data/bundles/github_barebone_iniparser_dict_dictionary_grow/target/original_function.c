static int dictionary_grow(dictionary * d)
{
    char        ** new_val ;
    char        ** new_key ;
    unsigned     * new_hash ;

    new_val  = (char**) calloc(d->size * 2, sizeof *d->val);
    new_key  = (char**) calloc(d->size * 2, sizeof *d->key);
    new_hash = (unsigned*) calloc(d->size * 2, sizeof *d->hash);
    if (!new_val || !new_key || !new_hash) {
        /* An allocation failed, leave the dictionary unchanged */
        if (new_val)
            free(new_val);
        if (new_key)
            free(new_key);
        if (new_hash)
            free(new_hash);
        return -1 ;
    }
    /* Initialize the newly allocated space */
    memcpy(new_val, d->val, d->size * sizeof(char *));
    memcpy(new_key, d->key, d->size * sizeof(char *));
    memcpy(new_hash, d->hash, d->size * sizeof(unsigned));
    /* Delete previous data */
    free(d->val);
    free(d->key);
    free(d->hash);
    /* Actually update the dictionary */
    d->size *= 2 ;
    d->val = new_val;
    d->key = new_key;
    d->hash = new_hash;
    return 0 ;
}