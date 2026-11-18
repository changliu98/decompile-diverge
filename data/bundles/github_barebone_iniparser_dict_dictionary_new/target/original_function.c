dictionary * dictionary_new(size_t size)
{
    dictionary  *   d ;

    /* If no size was specified, allocate space for DICTMINSZ */
    if (size<DICTMINSZ) size=DICTMINSZ ;

    d = (dictionary*) calloc(1, sizeof *d) ;

    if (d) {
        d->size = size ;
        d->val  = (char**) calloc(size, sizeof *d->val);
        d->key  = (char**) calloc(size, sizeof *d->key);
        d->hash = (unsigned*) calloc(size, sizeof *d->hash);
        if (!d->size || !d->val || !d->hash) {
            free((void *) d->size);
            free((void *) d->val);
            free((void *) d->hash);
            free(d);
            d = NULL;
        }
    }
    return d ;
}