int dictionary_grow(hashmap_t *hm) {
    char **new_val = (char **) calloc(hm->capacity * 2, sizeof(char *));
    char **new_key = (char **) calloc(hm->capacity * 2, sizeof(char *));
    unsigned int *new_hash = (unsigned int *) calloc(hm->capacity * 2,
            sizeof(unsigned int));

    if (!new_val || !new_key || !new_hash) {
        if (new_val)
            free(new_val);
        if (new_key)
            free(new_key);
        if (new_hash)
            free(new_hash);

        return -1;
    }

    memcpy(new_val, hm->val, hm->capacity * sizeof(char *));
    memcpy(new_key, hm->key, hm->capacity * sizeof(char *));
    memcpy(new_hash, hm->hash, hm->capacity * sizeof(unsigned int));

    free(hm->val);
    free(hm->key);
    free(hm->hash);

    hm->capacity *= 2;
    hm->val = new_val;
    hm->key = new_key;
    hm->hash = new_hash;

    return 0;
}