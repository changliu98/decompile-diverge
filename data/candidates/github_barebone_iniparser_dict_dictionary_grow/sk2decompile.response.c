static int dictionary_grow(dictionary *dict) {
  char **new_keys = calloc(dict->size * 2, sizeof(char *));
  char **new_values = calloc(dict->size * 2, sizeof(char *));
  unsigned int *new_hashes = calloc(dict->size * 2, sizeof(unsigned int));
  if (!new_keys || !new_values || !new_hashes) {
    if (new_keys) free(new_keys);
    if (new_values) free(new_values);
    if (new_hashes) free(new_hashes);
    return -1;
  }
  memcpy(new_keys, dict->keys, dict->size * sizeof(char *));
  memcpy(new_values, dict->values, dict->size * sizeof(char *));
  memcpy(new_hashes, dict->hashes, dict->size * sizeof(unsigned int));
  free(dict->keys);
  free(dict->values);
  free(dict->hashes);
  dict->size *= 2;
  dict->keys = new_keys;
  dict->values = new_values;
  dict->hashes = new_hashes;
  return 0;
}