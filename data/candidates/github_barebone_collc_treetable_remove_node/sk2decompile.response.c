void remove_node(tree_root* root, tree_node* node) {
  int old_color;
  tree_node* child;
  tree_node* y;
  if (node->left == root->nil) {
    child = node->right;
    transplant(root, node, child);
  } else if (node->right == root->nil) {
    child = node->left;
    transplant(root, node, child);
  } else {
    y = tree_min(root, node->right);
    old_color = y->color;
    child = y->right;
    if (y->parent == node) {
      child->parent = y;
    } else {
      transplant(root, y, y->right);
      y->right = node->right;
      y->right->parent = y;
    }
    transplant(root, node, y);
    y->left = node->left;
    y->left->parent = y;
    y->color = node->color;
  }
  if (old_color == 1) {
    rebalance_after_delete(root, child);
  }
  root->free(node);
  root->size--;
}