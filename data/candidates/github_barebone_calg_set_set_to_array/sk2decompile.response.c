void **set_to_array(set_t *set) {
  unsigned int i, j;
  set_node_t *node;
  void **array;
  array = malloc(set->size * sizeof(void *));
  if (array == NULL) return NULL;
  j = 0;
  for (i = 0; i < set->capacity; i++) {
    for (node = set->nodes[i]; node != NULL; node = node->next) {
      array[j] = node->data;
      j++;
    }
  }
  return array;
}