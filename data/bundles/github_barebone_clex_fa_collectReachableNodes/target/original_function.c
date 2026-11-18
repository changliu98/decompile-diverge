static bool collectReachableNodes(clexNode* start, NodeVec* nodes) {
  if (!start || !nodes) return false;
  if (!nodeVecPush(nodes, start)) return false;

  for (size_t i = 0; i < nodes->size; i++) {
    clexNode* node = nodes->items[i];
    for (size_t j = 0; j < node->transitionCount; j++) {
      if (!node->transitions[j] || !node->transitions[j]->to) continue;
      if (nodeVecContains(nodes, node->transitions[j]->to)) continue;
      if (!nodeVecPush(nodes, node->transitions[j]->to)) return false;
    }
  }
  return true;
}