static bool ensureNodeTransitionCapacity(clexNode* node, size_t required) {
  if (!node) return false;
  if (node->transitionCapacity >= required) return true;

  size_t newCapacity = node->transitionCapacity ? node->transitionCapacity : 4;
  while (newCapacity < required) {
    if (newCapacity > (size_t)-1 / 2) {
      newCapacity = required;
      break;
    }
    newCapacity *= 2;
  }

  clexTransition** resized =
      realloc(node->transitions, newCapacity * sizeof(clexTransition*));
  if (!resized) return false;
  memset(resized + node->transitionCapacity, 0,
         (newCapacity - node->transitionCapacity) * sizeof(clexTransition*));
  node->transitions = resized;
  node->transitionCapacity = newCapacity;
  return true;
}