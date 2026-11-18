static bool collectReachableNodes(Node *root, NodeVec *reachable) {
  if (root == NULL || reachable == NULL) return false;
  if (nodeVecPush(reachable, root) == NULL) return false;
  for (size_t i = 0; i < reachable->len; ++i) {
    Node *node = reachable->data[i];
    for (size_t j = 0; j < node->n_children; ++j) {
      if (node->children[j] == NULL || node->children[j]->node == NULL)
        continue;
      if (nodeVecContains(reachable, node->children[j]->node)) continue;
      if (nodeVecPush(reachable, node->children[j]->node) == NULL) return false;
    }
  }
  return true;
}