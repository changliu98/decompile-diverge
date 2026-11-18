static unsigned char ensureNodeTransitionCapacity(Node* node, size_t capacity) {
  if (node == NULL) {
    return 0;
  }
  if (node->transitionCapacity >= capacity) {
    return 1;
  }
  size_t newCapacity = node->transitionCapacity;
  if (newCapacity == 0) {
    newCapacity = 4;
  }
  while (newCapacity < capacity) {
    if (newCapacity > (((size_t)1) << 63) - 1) {
      newCapacity = capacity;
      break;
    }
    newCapacity *= 2;
  }
  Transition** newTransitions =
      realloc(node->transitions, newCapacity * sizeof(Transition*));
  if (newTransitions == NULL) {
    return 0;
  }
  memset(newTransitions + node->transitionCapacity, 0,
         (newCapacity - node->transitionCapacity) * sizeof(Transition*));
  node->transitions = newTransitions;
  node->transitionCapacity = newCapacity;
  return 1;
}