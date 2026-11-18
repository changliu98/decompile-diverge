struct HashTable *create_hash(size_t initial_size) {
    struct HashTable *hash;
    void *data;

    // Allocate 32 bytes for the HashTable structure
    hash = malloc(0x20);
    if (!hash) {
        return NULL;
    }

    // Allocate memory for the hash table data (initial_size * 8 bytes)
    data = malloc(initial_size * 8);
    hash->data = data;
    
    if (!hash->data) {
        free(hash);
        return NULL;
    }

    // Zero out the allocated data
    memset(hash->data, 0, initial_size * 8);

    // Set capacity and size
    hash->capacity = initial_size;
    hash->size = initial_size;

    return hash;
}