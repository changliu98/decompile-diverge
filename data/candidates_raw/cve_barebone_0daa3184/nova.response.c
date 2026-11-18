static struct entry *func0(struct hash *hash, const char *key, unsigned int len) {
    unsigned int hashval;
    struct entry *ep;

    if (len <= 6) {
        hashval = (key[0] << 8) | key[1];
        hashval = (hashval << 8) | key[2];
        hashval = (hashval << 8) | key[3];
    } else if (len <= 4) {
        hashval = (key[0] << 8) | key[1];
        hashval = (hashval << 8) | key[2];
        hashval = 0;
    } else {
        hashval = 0;
        hashval = (hashval << 8) | key[0];
        hashval = (hashval << 8) | key[1];
        hashval = (hashval << 8) | key[2];
    }

    for (ep = HASH_TABLE[hashval % HASH_SIZE]; ep!= NULL; ep = ep->next) {
        if (ep->hashval == hashval && ep->keylen == len &&
            memcmp(key, ep->key, len) == 0) {
            break;
        }
    }

    if (ep == NULL) {
        fprintf(stderr, "not found\n");
        ep = (struct entry *)calloc(1, sizeof(struct entry) + len + 1);
        ep->hashval = hashval;
        ep->keylen = len;
        memcpy(ep->key, key, len);
        ep->next = HASH_TABLE[hashval % HASH_SIZE];
        HASH_TABLE[hashval % HASH_SIZE] = ep;
    }

    return ep;
}