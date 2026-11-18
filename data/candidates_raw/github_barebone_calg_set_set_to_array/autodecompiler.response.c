void **
hash_keys(hash_t *h)
{
    void **rv;
    hash_entry_t *entry;
    unsigned int i, j;

    rv = malloc(h->num_entries * sizeof(void *));
    if (!rv) {
        rv = NULL;
        goto done;
    }

    j = 0;
    for (i = 0; i < h->size; i++) {
        entry = h->entries[i];
        while (entry) {
            rv[j] = entry->key;
            j++;
            entry = entry->next;
        }
    }

done:
    return rv;
}