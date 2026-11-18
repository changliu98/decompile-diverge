static void rebalance_after_delete(rbtree_t* tree, rbnode_t* node) {
  rbnode_t* child;
  while (node != tree->root && node->color == 1) {
    if (node == node->parent->left) {
      child = node->parent->right;
      if (child->color == 0) {
        child->color = 1;
        node->parent->color = 0;
        rotate_left(tree, node->parent);
        child = node->parent->right;
      }
      if (child->left->color == 1 && child->right->color == 1) {
        child->color = 0;
        node = node->parent;
      } else {
        if (child->right->color == 1) {
          child->left->color = 1;
          child->color = 0;
          rotate_right(tree, child);
          child = node->parent->right;
        }
        child->color = node->parent->color;
        node->parent->color = 1;
        child->right->color = 1;
        rotate_left(tree, node->parent);
        node = tree->root;
      }
    } else {
      child = node->parent->left;
      if (child->color == 0) {
        child->color = 1;
        node->parent->color = 0;
        rotate_right(tree, node->parent);
        child = node->parent->left;
      }
      if (child->right->color == 1 && child->left->color == 1) {
        child->color = 0;
        node = node->parent;
      } else {
        if (child->left->color == 1) {
          child->right->color = 1;
          child->color = 0;
          rotate_left(tree, child);
          child = node->parent->left;
        }
        child->color = node->parent->color;
        node->parent->color = 1;
        child->left->color = 1;
        rotate_right(tree, node->parent);
        node = tree->root;
      }
    }
  }
  node->color = 1;
}