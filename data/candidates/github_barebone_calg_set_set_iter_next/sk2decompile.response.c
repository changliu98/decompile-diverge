set_value_t set_iter_next(set_iter_t *iter) {
  set_t *set = iter->set;
  set_node_t *node;
  set_value_t value;
  unsigned int i;
  if (iter->node == NULL) {
    return NULL;
  }
  node = iter->node;
  value = node->value;
  if (node->next != NULL) {
    iter->node = node->next;
  } else {
    iter->node = NULL;
    for (i = iter->index + 1; i < set->size; i++) {
      if (set->nodes[i] != NULL) {
        iter->node = set->nodes[i];
        break;
      }
    }
    iter->index = i;
  }
  return value;
}