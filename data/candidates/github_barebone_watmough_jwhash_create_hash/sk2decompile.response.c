static hash_t *create_hash(unsigned int size) {
  hash_t *hash;
  hash = malloc(sizeof(hash_t));
  if (!hash) return NULL;
  hash->table = malloc(sizeof(hash_entry_t *) * size);
  if (!hash->table) {
    free(hash);
    return NULL;
  }
  memset(hash->table, 0, sizeof(hash_entry_t *) * size);
  hash->size = size;
  hash->max_size = size;
  return hash;
}